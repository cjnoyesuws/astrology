
#include <stdio.h>
#include <string.h>

#include "paths.hpp"

char *data_name( char const *name )
{
  return set_path( name, DATA_F );
}
