pushd ..\
pandoc README.md -o README.html
rem pandoc README.md --pdf-engine=xelatex -o README.pdf
popd
PAUSE