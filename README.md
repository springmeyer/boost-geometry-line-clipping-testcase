
This testcase clips a line once with a polygon and another time with a box using boost::geometry.


### Setup

Type:

```
make
```


It results in:

```
clipped via polygon:
    LINESTRING(-10 0,10 0)
clipped via box:
    LINESTRING(-20 0)
```

Why would clipping by a box result in a degenerate line?
