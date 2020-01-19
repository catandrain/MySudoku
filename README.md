# MySudoku 1120171389霍高原
数独终局的生成和求解项目
## intro
* BIN目录放置可执行的二进制文件，链接库和生成的数独终局
* 根目录放置代码和头文件
* 运行时请通过命令行运行**bin**目录下的可执行文件，使用 ./sudoku -c N生成终局，./sudoku -s PATH求解数独
## environment
* win10 1903
* C++
* VS2019
## struct
|————README.md  
|————BIN  
|>>>|————sudoku.exe  
|>>>|————sudoku.txt  
|>>>|————sudoku_finality.txt  
|>>>|————ques.txt  
|————main.cpp  
|————head.h  
|————func.cpp  
## tips
1. 生成的数独终局起名为sudoku_finality.txt,解决后的为sudoku.txt原因是个人文档中说的是例如使用sudoku.txt，但解决后的数独要求为sudoku.txt，为了防止重名，故分开。
2. ques.txt中有1000个数独题目。
3. 注意题目的要求，由于个人项目的pdf中要求问题之间空一行，但是示例中没空行，这里我默认使用的是空行的文件。也就是生成的和解决后的文件终局之间空了一行。
