
This testcase clips a line once with a polygon and another time with a box using boost::geometry.


### Setup

Type:

```
make
```

### Bug

In some versions of boost::geometry this testcase results in:

```
clipped via polygon:
    LINESTRING(-10 0,10 0)
clipped via box:
    LINESTRING(-20 0)
```

This was fixed in https://github.com/boostorg/geometry/pull/329
