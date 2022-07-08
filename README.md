# count

Counts lines on `stdin`.

Unline `wc` each matching count is printed. Therefore `count` might be used to display progress.

## Build

````
cmake -B build
cmake --build build
sudo cmake --build build --target install
````

## Examples

### Count lines

````
> echo -e "some\nline" | count
2
````

### Display progress

````
>  bash -c 'echo 1;sleep 1;echo 2;sleep 1' | count
3
````

### Use simple regular expressions

````
> echo -e "Apple\nOrange\nBanana" | count Apple Banana
2
````

### Use complex regular expressions

````
> echo -e "start\n10 %\n20 %\n30 %\n100 %\nfinished" | count '^\d\d %'
3
````
