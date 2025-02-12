- 1回目
	- fd (`STDIN`, `STDOUT`, 2,) pipe_fd(0, -1784390791)
	1. l.166 pipe
		fd(`STDIN`, `STDOUT`, 2,)
		pipe_fd(4, 5)
	2. l.179 dup2
		fd(`STDIN`, `STDOUT`(pipe[1]),  2)
		pipe_fd(4, 5)
	3. l.184 close(pipe_fd[1])
		fd(`STDIN`, `STDOUT`(pipe[1]),  2)
		pipe_fd(4, ~~5~~)
	4. l.187…fork
		1. 親…
			fd(`STDIN`, `STDOUT`(pipe[1]),  2)
			pipe_fd(4, ~~5~~)　
		2. 子…
			fd(`STDIN`, `STDOUT`(pipe[1]),  2)
			pipe_fd(4, ~~5~~)
	5. l.196…子プロセス実行
		1. `/usr/bin/ls`を実行
		2. `STDIN`(pipe[0])から入り、`STDOUT`(pipe[1])に出力??
		3. memo:pipe_fd[0]をcloseしてない→やらなくても良さそう。やったほうが安心
- 2回目
	1. 親
		fd(`STDIN`, `STDOUT`(pipe[1]),  2)
		pipe_fd(4, ~~5~~)　
	2. l.160 … dup2
		fd(`STDIN`(pipe[0]), `STDOUT`(pipe[1]),  2)
		pipe_fd(4, ~~5~~)　
		1. `STDOUT`(pipe[1])を`STDIN`(pipe[0])に流す??
	3. l.162 … close
		fd(`STDIN`(pipe[0]), `STDOUT`(pipe[1]),  2)
		pipe_fd(~~4~~, ~~5~~)　
	4. l.166 … pipe
		fd(`STDIN`(pipe[0]), `STDOUT`(pipe[1]),  2)
		pipe_fd(4, 5)???
	5. l.174 … dup2(fd, STDOUT_FILENO)
		fd(`STDIN`(pipe[0]), `STDOUT`(outfile_fd),  2)
		pipe_fd(4, 5)
	5. l.184 … close(pipe_fd[1])
		fd(`STDIN`(pipe[0]), `STDOUT`(outfile_fd),  2)
		pipe_fd(4, ~~5~~)
	6. l.187…fork
		1. 親…
			fd(`STDIN`(pipe[0]), `STDOUT`(outfile_fd),  2)
			pipe_fd(4, ~~5~~)　
		2. 子…
			fd(`STDIN`(pipe[0]), `STDOUT`(outfile_fd),  2)
			pipe_fd(4, ~~5~~)
	7. l.196…子プロセス実行
		1. `/usr/bin/wc`を実行
		2. `STDIN`(pipe[0])から入り、`STDOUT`(outfile_fd)に出力
		3. memo:最後はpipeを作る必要ないのでは？


## pipe_fdの扱い
	- first_cmd
		1. pipe_fd[0]　→ 使わない
		2. pipe_fd[1]　→ 使う
	- middle_cmd
		1. pipe_fd[0]　→ 使う
		2. pipe_fd[1]　→ 使う
	- last_cmd
		1. pipe_fd[0]　→ 使う
		2. pipe_fd[1]　→ 使わない

## pipe_fdの流れ
	- first_cmd
		pipe();
		dup2();→STDOUTをpipe_fd[1]に
		close();→pipe_fd[1]をclose

		子：pipe_fd[0]
		親：pipe_fd[0]
	- middle_cmd
		dup2();→STDINをpipe_fd[0]に
		close();→pipe_fd[0]をclose
		pipe();
		dup2();→STDOUTをpipe_fd[1]に
		close();→pipe_fd[1]をclose

		子：pipe_fd[0]
	- last_cmd
		dup2();→STDINをpipe_fd[0]に
		close();→pipe_fd[0]をclose
		dup2();→STDOUTをfd_outに

		子：
		親：


- first_cmd関数とmiddle_cmd関数で、close(pipe_fd[0])しない場合
	```
	# Processes on 68976
	-+= 68976 miyuu -zsh -g --no_rcs
	\-+= 72596 miyuu bash
	\-+= 19821 miyuu ./a.out cat cat ls
		|--- 19827 miyuu /bin/cat
		\--- 19828 miyuu /bin/cat

	# fds on 19828
	COMMAND   PID  USER   FD   TYPE             DEVICE SIZE/OFF
	NODE NAME
	cat     19828 miyuu  cwd    DIR               1,18      480           123
	996843 /Users/miyuu/Library/CloudStorage/OneDrive-kuwasawa.ac.jp/Desktop/
	17_42tokyo/42cursus/pipex/mfunakos
	cat     19828 miyuu  txt    REG               1,18   119040 1152921500312
	497683 /bin/cat
	cat     19828 miyuu  txt    REG               1,18  2423888 1152921500312
	499566 /usr/lib/dyld
	cat     19828 miyuu    0   PIPE  0x7def1b2793b0643    16384
		->0x76ccbc4e430d6f9
	cat     19828 miyuu    1   PIPE  0x5228f1b91ca92d7    16384
		->0x241d421e6dca5b1b
	cat     19828 miyuu    2u   CHR               16,1  0t70576
	785 /dev/ttys001
	cat     19828 miyuu    3u   CHR               16,1  0t70576
	785 /dev/ttys001
	cat     19828 miyuu    4   PIPE 0x241d421e6dca5b1b    16384


- first_cmd関数とmiddle_cmd関数で、close(pipe_fd[0])する場合
	```
	Processes on 68976
	-+= 68976 miyuu -zsh -g --no_rcs
	\-+= 72596 miyuu bash
	\-+= 21064 miyuu ./a.out cat cat ls
		|--- 21078 miyuu /bin/cat
		\--- 21079 miyuu /bin/cat

	# fds on 21079
	COMMAND   PID  USER   FD   TYPE             DEVICE SIZE/OFF
	NODE NAME
	cat     21079 miyuu  cwd    DIR               1,18      480           123
	996843 /Users/miyuu/Library/CloudStorage/OneDrive-kuwasawa.ac.jp/Desktop/
	17_42tokyo/42cursus/pipex/mfunakos
	cat     21079 miyuu  txt    REG               1,18   119040 1152921500312
	497683 /bin/cat
	cat     21079 miyuu  txt    REG               1,18  2423888 1152921500312
	499566 /usr/lib/dyld
	cat     21079 miyuu    0   PIPE 0x6e55f8033641e6b1    16384
		->0xf357a9c29ee53788
	cat     21079 miyuu    1   PIPE 0x9d1cb2b28c258e7d    16384
		->0xe930dd9cd586a764
	cat     21079 miyuu    2u   CHR               16,1  0t70678
	785 /dev/ttys001
	cat     21079 miyuu    3u   CHR               16,1  0t70678
	785 /dev/ttys001
