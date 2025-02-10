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
