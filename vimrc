set background=dark
set ts=2 sw=2
syntax on 
set nocompatible 
set autochdir 
set autoindent 
set backspace=2 
set cindent 
set foldopen-=search 
set hlsearch 
set ignorecase 
set iminsert=0 
set imsearch=-1 
set incsearch 
set langmenu=en_US.UTF-8 
set nocompatible 
set nocursorline 
set number 
set ruler 
set smartcase 
set smartindent

let g:ale_enabled = 1
let g:ale_c_build_dir = '/home/ajit_a/learn' 
let g:ale_cpp_parse_compile_commands = 1 
let g:ale_open_list = 1 
let g:ale_set_quickfix = 1 
let g:ale_completion_enabled = 1
let g:ale_cpp_clangtidy_executable = '/home/ajit_a/learn/clang-tidy'
let g:ale_linters = {
	\ 'cpp' : ['clangtidy'],
	\ 'c'   : ['clangtidy'],
	\}
let g:ale_fixers = {
	\ 'cpp' : ['clang-format'],
	\ 'c' : ['clang-format'],
	\ '*'   : ['remove_trailing_lines','trim_whitespace'],
\}
