
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
	//Variables
	char c1,c2;
	int no_of_bytes_read =0,no_of_bytes_read2 =0;
	int fd1 = 0, fd2 = 0;
	
	//Open each file that we recieved his path from the arguments
	fd1 = open( argv[1] , O_RDONLY );
	if (fd1 == -1){
		perror( "Could not open file1" );
		exit(-1);
	}

	fd2 = open( argv[2] , O_RDONLY );
	if(fd2 == -1){
		close(fd1);
		perror( "Could not open file2" );
		exit(-1);
	}
	
	//Strat to read bit bit from each file and compare them.
	//I've chose do{} whlie() to enter to the loop for the first iteration due to no of bytes to read is 0.
	do{
		no_of_bytes_read = read(fd1,&c1,1);
		no_of_bytes_read2 = read(fd2,&c2,1);
		if(no_of_bytes_read < 0 || no_of_bytes_read2 < 0)
		{
			close(fd1);
			close(fd2);
			perror("Could not read from a file");
			exit(-1);
		}
		
		if(c1 != c2)  // check if the chars are different if "TRUE" we can return 1
		{
		close(fd1);
		close(fd2);
		return 1;
		}
		
	} while(no_of_bytes_read > 0 && no_of_bytes_read2 > 0);
	// As long as the no of bytes to read bigger than 0 we aren't at the end of the file.
	//When the no of bytes to read will be 0 it's mean that we didn't read anything so we can conclude that we are at the end of the file.
	
	//If we get out from the loop it's mean that the files are equal and we can return 1
	close(fd1);
	close(fd2);
	return 2;
}
