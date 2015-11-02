
/*loadSequence takes a filename, loads all the alphabetic characters in the
  file into a string (converting to upper case) and returns the string, or NULL
  on error*/
char *loadSequence(char *filename) {
  FILE *seqFile;    /*pointer to sequence file*/
  char *seqString;  /*sequence string*/
  int i = 0;        /*iterator*/
  int fileLength;   /*store length of file--so can malloc string once*/
  int c;            /*hold current character off of file stream*/

  if(!(seqFile = fopen(filename, "r"))) { /*if file is unopenable, exit*/
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return(NULL);
  }

  fseek(seqFile, 0, SEEK_END);        /*move file pointer to end of file*/
  fileLength = (int) ftell(seqFile);  /*store offset from beginning (size)*/

  if(!fileLength) {                   /*file is of length zero*/
    fclose(seqFile);
    fprintf(stderr, "File %s contains no data\n", filename);
    return(NULL);
  }

  if(fileLength == INT_MAX) {          /*file too long for this simple program*/
    fclose(seqFile);
    fprintf(stderr, "Sequence in %s is too long for this program!\n", filename);
    return(NULL);
  }

  seqString = (char *) malloc((fileLength + 1) * sizeof(char)); /*roomfor '\0'*/
  rewind(seqFile);                    /*go back to beginning to read file*/

  while((c = fgetc(seqFile)) != EOF)   /*read until end-of-file*/
    if(isalpha(c))
      seqString[i++] = (char) toupper(c);

  fclose(seqFile);

  seqString[i] = '\0';                /*null-terminate string*/
  return(seqString);
}
