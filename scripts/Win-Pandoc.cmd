pushd ..\
rem pandoc README.md -o README.html
pandoc README.md --pdf-engine=xelatex -o README.pdf
popd
PAUSE