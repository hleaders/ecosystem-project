# Area map

Area map is a two-dimensional grid of characters, where each character represents either open space or designates the current position of a living organism.

Specifically, the space character (` `) represents open space. Living organisms (plants and animals) are referenced using their corresponding one-letter identifiers as defined in the [list of species](Species.md).

Here's an example of a 10x10 area map ([source](map.txt)) that corresponds to [this](species.txt) list of species:
```
        aa
b     D   
          
 a a   B  
   a  A   
          
bb        
b         
 bbb      
      C   
```
