for file in ./**/*.s ; do printf $file; printf "\n"; ../../asm/asm $file; done