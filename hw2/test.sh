echo $'1\n2\n3' > file1.txt
echo $'1\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">1 2 3\n"

echo $'1\n22\n3' > file1.txt
echo $'1\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">1 -22 +2 3\n"

echo $'1\n2\n3' > file1.txt
echo $'1\n22\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">1 -2 +22 3\n"

echo $'1\n2\n33' > file1.txt
echo $'1\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">1 2 -33 +3\n"

echo $'1\n2\n3' > file1.txt
echo $'1\n2\n33' > file2.txt
sbcl --script diff.lsp
echo -e ">1 2 -3 +33\n"

echo $'11\n2\n3' > file1.txt
echo $'1\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">-11 +1 2 3\n"

echo $'1\n2\n3' > file1.txt
echo $'11\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">-1 +11 2 3\n"

echo $'1\n2\n2\n3' > file1.txt
echo $'1\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">1 -2 2 3\n"

echo $'1\n2\n2\n3' > file1.txt
echo $'1\n2\n2\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">1 +2 2 2 3\n"

echo $'1\n2\n2\n3' > file1.txt
echo $'1\n2\n3\n2\n2' > file2.txt
sbcl --script diff.lsp
echo -e ">1 +2 +3 2 2 -3\n"

echo $'1\n2\n2\n3' > file1.txt
echo $'1\n2\n2\n3\n2\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">1 +2 +2 +3 2 2 3\n"

echo $'1\n2\n2\n3' > file1.txt
echo $'1\n4\n4\n5' > file2.txt
sbcl --script diff.lsp
echo -e ">1 -2 -2 -3 +4 +4 +5\n"

echo $'' > file1.txt
echo $'1\n2\n3' > file2.txt
sbcl --script diff.lsp
echo -e ">- +1 +2 +3\n"

echo $'1\n2\n3' > file1.txt
echo $'' > file2.txt
sbcl --script diff.lsp
echo -e ">-1 -2 -3 +\n"
