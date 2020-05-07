//----------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                                                                                                                      //
//                                                                                                                                                                      //
//                                            TIPs & TRICKS - MEMO TECHNIQUE C_Text Processing Functions                                                                //
//                                                                                                                                                                      //
// Copyright (c) 2017-2018 MDO                                                                                                                                          //
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------//


// --------------------------------------Fonction 1 --------------------------------------
//
// Description:
//    Search for and replace text within a string.
//
// Parameters:
//    src (in) - pointer to source string
//    from (in) - pointer to search text
//    to (in) - pointer to replacement text
//
// Returns:
//    Returns a pointer to dynamically-allocated memory containing string
//    with occurences of the text pointed to by 'from' replaced by with
//    the text pointed to by 'to'.
//
// --------------------------------------Fonction 1 --------------------------------------
char *strReplace(const char *src, const char *from, const char *to)
{
  char *value;
  char *dst;
  char *match;
  int size;
  int fromlen;
  int tolen;
 
  // Find out the lengths of the source string, text to replace, and
  // the replacement text.
  size = strlen(src) + 1;
  fromlen = strlen(from);
  tolen = strlen(to);
 
  // Allocate the first chunk with enough for the original string.
  value = (char *)malloc(size);
 
  // We need to return 'value', so let's make a copy to mess around with.
  dst = value;
  
  // Before we begin, let's see if malloc was successful.
  if ( value != NULL )
  {
    // Loop until no matches are found.
    for ( ;; )
    {
      // Try to find the search text.
      match = (char *) strstr(src, from);
      if ( match != NULL )
      {
        // Found search text at location 'match'.
        // Find out how many characters to copy up to the 'match'.
        size_t count = match - src;
 
        // We are going to realloc, and for that we will need a
        // temporary pointer for safe usage.
        char *temp;
 
        // Calculate the total size the string will be after the
        // replacement is performed.
        size += tolen - fromlen;
 
        // Attempt to realloc memory for the new size.
        //
        // temp = realloc(value, size);
        temp = (char *)realloc(value, size);
 
        if ( temp == NULL )
        {
          // Attempt to realloc failed. Free the previously malloc'd
          // memory and return with our tail between our legs.
          free(value);
          return NULL;
        }
 
        // The call to realloc was successful. But we'll want to
        // return 'value' eventually, so let's point it to the memory
        // that we are now working with. And let's not forget to point
        // to the right location in the destination as well.
        dst = temp + (dst - value);
        value = temp;
 
        // Copy from the source to the point where we matched. Then
        // move the source pointer ahead by the amount we copied. And
        // move the destination pointer ahead by the same amount.
        memmove(dst, src, count);
        src += count;
        dst += count;
 
        // Now copy in the replacement text 'to' at the position of
        // the match. Adjust the source pointer by the text we replaced.
        // Adjust the destination pointer by the amount of replacement
        // text.
        memmove(dst, to, tolen);
        src += fromlen;
        dst += tolen;
      }
      else // No match found.
      {
        // Copy any remaining part of the string. This includes the null
        // termination character.
        strcpy(dst, src);
        break;
      }
    } // For Loop()
  }
  return value;
}



// --------------------------------------Fonction 2 --------------------------------------
//
// Description:
//		This function allow to read a file, search for, replace text within a string and save
//		into a new file after le processing.
//
// Parameters:
//    const char fileReadName[1000], const char *from, const char *to, const char fileOutputName[1000]
//    fileReadName (in) - tab contains the source file name (Ex: char filename1[1000] = "file.txt";)
//	  fileOutputName (in) - tab contains the output file name 
//    from (in) - pointer to search text
//    to (in) - pointer to replacement text
//
// Returns:
//    Returns a pointer to dynamically-allocated memory containing string
//    with occurences of the text pointed to by 'from' replaced by with
//    the text pointed to by 'to'.
//
// Notes:
//    Do not use this directly in scripts unless you are a more advanced
//    user who knows C and string handling. See below for the function you
//    should use!
//
// --------------------------------------Fonction 2 --------------------------------------

char * strReplaceFile(const char fileReadName[1000], const char *from, const char *to, const char fileOutputName[1000])
{
	long fileRead	= fopen ( fileReadName, "r+" );
	long fileOutput	= fopen ( fileOutputName, "w+" );
	char line [ 4000 ];
	char tempLine [ 4000 ]; // cette valeur permet de stocker la ligne fraichement traitée
	
	if (( fileRead != NULL ) && ( fileOutput != NULL ))
   {
      while ( fgets ( line, 100, fileRead ) != NULL ) /* read a line */
      {
//      	lr_output_message( "The first line is \"%s\"", line);
			strcpy(tempLine, strReplace(line, from, to));
			fprintf(fileOutput, tempLine);
//		lr_output_message( "The convert line is \"%s\"", tempLine);
//			fprintf(fileOutput, "\n");
      }
      fclose ( fileRead );
      fclose ( fileOutput );
   }
   else 
   {
		lr_error_message("Cannot open or not extist : %s (processing file)", fileReadName);

		return 0;
   }
//   lr_output_message( "File processing is successfully ended");
	return 0;
}

// --------------------------------------Fonction 3 --------------------------------------
//
// Description:
//		This function allow to read a file, search for, delete text (or text groups) and save
//		into a new file after le processing.
//
// Parameters:
//    const char fileReadName[1000], const char *from, const char *to, const char fileOutputName[1000]
//    fileReadName (in) - tab contains the source file name (Ex: char filename1[1000] = "file.txt";)
//	  fileOutputName (in) - tab contains the output file name 
//    separator (in) - pointer to delete text
//    join (in) - pointer to the type of join between tow splitted tokens 
//
// Returns:
//    Returns a file to dynamically-allocated memory containing string
//    with occurences of the text pointed to by 'separator' deleted
//	  and to join all of these tokens by 'join'.
//
// Notes:
//    Do not use this directly in scripts unless you are a more advanced
//    user who knows C and string handling. See below for the function you
//    should use!
//
// --------------------------------------Fonction 3 --------------------------------------

char * strSpliter(const char fileReadName[1000], const char separators[100], const char *join, const char fileOutputName[1000])
{
	
	char MonMot[1024];
//    char separators[] = ".\\"; 
    char *token;
    char *temp;

	long fileRead	= fopen ( fileReadName, "r+" );
	long fileOutput	= fopen ( fileOutputName, "w+" );
	char line [ 4000 ];
	char tempLine [ 4000 ]; // cette valeur permet de stocker la ligne fraichement traitée
	
	if (( fileRead != NULL ) && ( fileOutput != NULL ))
   {
      while ( fgets ( line, 100, fileRead ) != NULL ) /* read a line */
      {
//      	lr_output_message( "The first line is \"%s\"", line);
//			strcpy(tempLine, strReplace(line, from, to));
			
/*---------------------------------------------------------------------*/			
			
			// Get the first token 
			token = (char *)strtok(line, separators);
//			lr_output_message ("%s", token );
			//    strcpy(MonMot,token);
//        lr_output_message ("%s", MonMot );
        if (!token) 
        {
        	lr_output_message ("No tokens found in string!");
        	return 0;
        }
        // While valid tokens are returned
        while (token != NULL ) 
        {
        	lr_output_message ("%s", token );
        	strcat(tempLine, token);
        	strcat(tempLine, join);
        	lr_output_message ("hehe %s", tempLine );
        	// Get the next token
        	token = (char *)strtok(NULL, separators);
        }
        lr_output_message ("%s", tempLine );	
			
/*------------------------------------------------------------*/			
		fprintf(fileOutput, tempLine);
//		strcpy(tempLine,"");
//		lr_output_message( "The convert line is \"%s\"", tempLine);
//			fprintf(fileOutput, "\n");
      }
      fclose ( fileRead );
      fclose ( fileOutput );
   }
   else 
   {
		lr_error_message("Cannot open or not extist : %s (processing file)", fileReadName);

		return 0;
   }
//   lr_output_message( "File processing is successfully ended");
	return 0;
}

