#include "function_maths.h"
#include "get_next_line.h"
#include "libft.h"
#include "parsing.h"

int main(int argc, char *argv[])
{

 //main_parsing(argv[1]);
 if (argc == 2)
 {
    main_function(argv[1]);
    
 }
  else 
  {
    printf("Error\n");
    exit(EXIT_FAILURE);
  }
}