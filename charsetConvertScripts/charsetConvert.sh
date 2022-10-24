#!/bin/bash

# These commands use 'enca' to detect a file's encoding and convert them
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

# Use 'find' to generate a list of input files
# find . -type f | xargs enconv -L zh -x utf-8

# Use 'ls' to generate a list of input files
# ls | xargs enconv -L zh -x utf-8

# Provide a list of input file's path (each path per line in "fileList")
# xargs enconv -L zh -x utf-8 < fileList

# Deprecated implement
# vvvvvvvvvvvvvvvvvvvv

# #!/bin/bash

# # setting target root path
# rootPath=/home/mfj/projects/LuckyFrameClient/

# # read every regular file
# # for every file, read its encoding, then call iconv
# for aFile in $(find $rootPath -type f);
# do
#     aFileEncoding=$(file -b --mime-encoding $aFile)
#     aFileConv=$aFile"utf-8"
#     # echo $aFileConv
#     # if binary or utf8 or us-ascii then continue
#     if [ "$aFileEncoding" == "binary" -o "$aFileEncoding" == "utf-8" -o "$aFileEncoding" == "us-ascii" ]; then
#         continue;
#     # if unknown-8bit or iso-8859-1 then iconv -f gbk
#     elif [ "$aFileEncoding" == "unknown-8bit" -o "$aFileEncoding" == "iso-8859-1" ]; then
#         # set -x
#         # read
#         iconv --verbose -o $aFileConv -f gbk -t utf-8 $aFile
#         if [ $? -ne 0 ]; then
#             echo $aFile ':'
#             echo "from $aFileEncoding to utf-8"
#             exit 1;
#         fi
#         mv $aFileConv $aFile
#         # set +x;
#     # else echo unknown encoding---------------------------
#     else
#         echo $aFile ':'
#         echo "unknown encoding -----------------------------------------------"
#     fi
# done
