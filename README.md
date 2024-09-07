# Sorting Values With MPI

In `src/main.cpp`, you will find a code that initializes each rank with a random vector (named `sortvec`) of size `nvalues_per_rank`.  Your task is to sort the `sortvec` vectors across all ranks, so that all the values in `sortvec` for rank `1` are larger than those of rank `0`, all of the values in `sortvec` for rank `2` are larger than those of rank `1`, *etc*.
Additionally, the values of `sortvec` for each rank should increase with increasing index.
For example, if `nvalues_per_rank` is `2` and you run on three ranks, your sorted values might look like:

```
Values on rank 0
   Index: 0   Value: 0.085082
   Index: 1   Value: 0.231541
Values on rank 1
   Index: 0   Value: 0.392845
   Index: 1   Value: 0.540266
Values on rank 2
   Index: 2   Value: 0.847946
   Index: 3   Value: 0.875252
```

There are many different ways to do this.
You must perform the calculation in a way that ensures that the amount of data required by each individual rank is independent of the total number of ranks (at least, beyond the first handful of ranks).
For example, you are **not** permitted to simply gather all of the data from every rank's `sortvec` onto rank `0` and then have rank `0` do the complete sort - aside from being computationally inefficient, that would be a wasteful way to handle memory resources.
It might be helpful to know that there are [named algorithms](https://en.wikipedia.org/wiki/Odd%E2%80%93even_sort) for handling this type of problem.
