# List of species

Each line in the list represents a single species, starting with the species category (`plant`, `herbivore`, `omnivore`), followed by a one-letter species identifier, followed by the list of the species' characteristics. The list of characteristics differs between the plants and the animals:

| Grammar | Example |
| ---------- | ---------- |
| `plant` _\<one-letter id\> \<regrowth coefficient\> \<energy points\>_ | `plant a 2 10` |
| `herbivore` _\<one-letter id\>_ _\<max energy level\>_  | `herbivore A 20` |
| `omnivore` _\<one-letter id\>_  _\<max energy level\>_  | `omnivore C 40` |

Here's an example list of species that can be used together with [this area map](map.txt):

```
plant a 1 5
plant b 3 10
herbivore A 20
herbivore B 15
omnivore C 40
omnivore D 30
```
