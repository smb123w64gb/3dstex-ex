# 3dstex-ex
**Texture conversion utility for Nintendo 3DS.**

Working to add diffrent formats to convert directly to 3DS Game formats.

Originaly [3dstex](https://github.com/Cruel/3dstex)

Usage:
  ./3dstex-ex [options] input output
  ./3dstex-ex -b [options] files ...

Options:
  -r           Raw output without header. Header is added by default.
  -p           Print info of input files instead of encoding them.
  -h           Print this help information.
  -b           Batch mode. Converts all input files, gives them *.bin outputs.
  -d <dir>     Directory to output files. Only for batch mode.
               Defaults to the directory of inputs.
  -c <level>   Quality level for ETC1 compression:
                 1  - Low quality    (fast)
                 2  - Medium quality (default)
                 3  - High quality   (slow)
  -i <format>  Input format type. Only needed when input files have no header.
               Possible types: rgba8, rgb8, rgba5551, rgb565, rgba4, la8, hilo8,
               l8, a8, la4, l4, a4, etc1, etc1a4.
  -o <format>  Output format type. Can be any of the above input types with some
               additional special types:
                 png        - PNG output, disabling alpha channel if not used.
                 auto-etc1  - ETC1 when input has no alpha, otherwise ETC1A4.
                 auto-l8    - L8 when input has no alpha, otherwise LA8.
                 auto-l4    - L4 when input has no alpha, otherwise LA4.
```

## Examples

Convert all PNGs in current directory to ETC1(A4) using batch mode:
```
$ 3dstex-ex -bo auto-etc1 *.png
```

Convert image to ETC1 in `output` directory using batch mode and max quality compression (3):
```
$ 3dstex-ex -o etc1 -bd output -c 3 image.png
```

Convert image to raw (no header) LA8:
```
$ 3dstex-ex -ro la8 image.jpg texture.bin
```

Convert ETC1A4 texture to RGBA4:
```
$ 3dstex-ex -i etc1a4 -o rgba4 input.bin output.bin
```

## Header
By default, output has a 10 byte header for convenience when reading it. This can be disabled with the `-r` flag.

The header contains original input dimensions in the case that you want to convert and use images of arbitrary (NPOT) dimensions.

Header is defined as the following:
```c
typedef struct
{
	u16 format;         //< Format matching ctrulib enum GPU_TEXCOLOR
	u16 width;          //< Width (original width to next power of 2)
	u16 height;         //< Height (original height to next power of 2)
	u16 widthOriginal;  //< Width of original input
	u16 heightOriginal; //< Height of original input
} Header;
```

## Input

Currently supports PNG and JPEG input (using stb_image) with some [minor restrictions](https://github.com/nothings/stb/blob/master/stb_image.h#L23-L24).

You can use previously converted textures as input too, but if they're raw (with no header), you need to specify the format using the `-i` flag.
