# SFTP

Simple file transfer protocol, including server and client.

Prerequisites:
	* Linux
	* C++11 Compiler
	* Make

Running instructions:
	1. From terminal of root folder, run "make all"
	2. In on terminal run "./server"
	3. In another run "./client"
	4. From here we only interact with the client terminal
	5. Press "enter" twice to use default IP and port (127.0.0.1:10000)
	6. Commands can now be entered into the client

Support instructions as per RFC 913 for SFTP:
	USER <user_id>
	ACCT <account_name>
	PASS <password>
	TYPE {A | B | C}
	LIST {F | V} <optional_directory_path>
	CDIR <new_directory>
	KILL <filename>
	NAME <old_file>
		TOBE <new_name>
	DONE
	RETR <filename>
		SEND
		STOP
	STOR {NEW | OLD | APP} <filename>
		SIZE <number_of_bytes>

Testing instructions:

To test a specific command simply enter the command and its required inputs to the client terminal.
Spaces are required between commands and arguments. {} braces contain flags of which only one can
be set. <> contain unique arguments for each of the commands.

Users are defined in the "users.txt" file in the root directory, there are a max of 10 users with
each line of the file defining a user in the format of:
	<user> <account> <password>


USER <user_id>
	Enters the remote system's user_id to the server. Exluding the DONE command, this must be
	the first entered. Compares against users defined in users.txt

	Example usage:
		USER TEST
			Sets user_id as TEST

ACCT <account_name>
	Enters the remote system's account name to the server. Compares against accounts belonging
	to specific users defined in users.txt. Fails if account doesn't match the user.

	Example usage:
		ACCT BLAIN
			Sets account as BLAIN

PASS <password>
	Enters the remote system's password to the server fails unless its matches both user and
	account defined in users.txt

	Example usage:
		PASS CRIBB
			Sets password as CRIBB

TYPE {A | B | C}
	Change the file transfer type. A is ASCII, B is binary and C is continuous.

	Example usage:
		TYPE A
			Sets the transfer type as ASCII
		TYPE B
			Sets the transfer type as binary

LIST {F, V} <optional_directory_path>
	List files in current directory, or optional_directory_path from the current directory.
	The F flag is the normal mode which just lists filenames, folders and transitions. The
	V flag is verbose listing which also displays filesize in bytes.

	Example usage:
		LIST F
			Display all files from current directory
		LIST V testfolder
			Displays all files and filesizes in the testfolder subdirectory

CDIR <new_directory>
	Appends new_directory to the end of the current directory path. Can set new_directory
	as ".." to move up a level.

	Example usage:
		CDIR testfolder
			Change working directory to testfolder subdirectory
		CDIR ..
			Move up one level to the superdirectory of current path

KILL <filename>
	Deletes filename in current working directory of server.

	Example usage:
		KILL BeeMovie
			Deletes BeeMovie file on server
		KILL testfolder/inner
			Detetes inner file in testfolder subdirectory

NAME <old_file>
	Prepares old_file for renaming. Should be immediately followed by TOBE command or
	renaming will be aborted

	Example usage:
		NAME BeeMovie
			Prepares BeeMovie for renaming

TOBE <new_name>
	Renames previously selected file (from NAME command) to new_name

	Example usage:
		TOBE BarryBBee
			Renames previously chosen file to BarryBBee

DONE
	Notifies server that you have completed all operations and both client and server close
	the connection. Server should wait for new connection and clear previous data (e.g - 
	logged in user, password, etc) and client should ask for new IP and port to connect to.

	Example usage:
		DONE
			Closes connection with server

RETR <filename>
	Requests that the server send specified filename. Server responds with filesize of
	requested file. Should be immediately followed by either SEND or STOP command.

	Example usage:
		RETR BeeMovie
			Requests the BeeMovie file from the server

SEND
	Sends previously queued file from the server.

STOP
	Stops the previously queued files from being sent.

STOR {NEW | OLD | APP} <filename>
	Requests that the server accept filename from the clients working directory. The NEW
	flag means that we will create a new generation of the file if filename already exists 
	with (x) appended where x is the lowest number that doesn't exist, or create a file with
	filename if it doesnt already exist. The OLD flag means we will overwrite the current
	filename file if it already exists or create a new file if it does. APP means we append
	to filename if it already exists or creates a new one if it doesn't. Requires that
	filename exists within client_files folder. Requires follow up commands such as SIZE which
	are automatically handled by the client.

	Example usage:
		STOR NEW BeeMovie
			Requests that the server creates new generation of BeeMovie file
		STOR APP BeeMovie
			Appends BeeMovie files contents to the end of the BeeMovie file.


