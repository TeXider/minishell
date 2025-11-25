# Diff Details

Date : 2025-11-25 14:55:36

Directory /home/tpanou-d/Documents/github/minishell/macrochibre/

Total : 53 files,  985 codes, 266 comments, 124 blanks, all 1375 lines

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [macrochibre/.main.c](/macrochibre/.main.c) | C | 36 | 11 | 7 | 54 |
| [macrochibre/builtins/.deprecated\_export.c](/macrochibre/builtins/.deprecated_export.c) | C | 138 | 11 | 15 | 164 |
| [macrochibre/builtins/builtin\_cd.c](/macrochibre/builtins/builtin_cd.c) | C | 126 | 11 | 12 | 149 |
| [macrochibre/builtins/builtin\_echo.c](/macrochibre/builtins/builtin_echo.c) | C | 32 | 11 | 5 | 48 |
| [macrochibre/builtins/builtin\_env.c](/macrochibre/builtins/builtin_env.c) | C | 12 | 11 | 3 | 26 |
| [macrochibre/builtins/builtin\_exit.c](/macrochibre/builtins/builtin_exit.c) | C | 43 | 11 | 6 | 60 |
| [macrochibre/builtins/builtin\_export.c](/macrochibre/builtins/builtin_export.c) | C | 87 | 26 | 10 | 123 |
| [macrochibre/builtins/builtin\_pwd.c](/macrochibre/builtins/builtin_pwd.c) | C | 11 | 11 | 3 | 25 |
| [macrochibre/builtins/builtin\_unset.c](/macrochibre/builtins/builtin_unset.c) | C | 27 | 11 | 5 | 43 |
| [macrochibre/builtins/util\_convert\_export\_to\_var.c](/macrochibre/builtins/util_convert_export_to_var.c) | C | 68 | 27 | 11 | 106 |
| [macrochibre/builtins/util\_envp.c](/macrochibre/builtins/util_envp.c) | C | 31 | 43 | 7 | 81 |
| [macrochibre/builtins/util\_exportp.c](/macrochibre/builtins/util_exportp.c) | C | 53 | 54 | 9 | 116 |
| [macrochibre/builtins/util\_find\_var.c](/macrochibre/builtins/util_find_var.c) | C | 36 | 11 | 6 | 53 |
| [macrochibre/builtins/util\_safe\_getcwd.c](/macrochibre/builtins/util_safe_getcwd.c) | C | 11 | 11 | 2 | 24 |
| [macrochibre/builtins/util\_throw\_builtin\_error.c](/macrochibre/builtins/util_throw_builtin_error.c) | C | 33 | 12 | 6 | 51 |
| [macrochibre/create\_error.c](/macrochibre/create_error.c) | C | 2 | 0 | 0 | 2 |
| [macrochibre/exec/.get\_path\_main.c](/macrochibre/exec/.get_path_main.c) | C | 21 | 11 | 3 | 35 |
| [macrochibre/exec/exec\_cmd\_line.c](/macrochibre/exec/exec_cmd_line.c) | C | 0 | 0 | -1 | -1 |
| [macrochibre/exec/get\_path.c](/macrochibre/exec/get_path.c) | C | 79 | 11 | 9 | 99 |
| [macrochibre/exec/open\_redirs.c](/macrochibre/exec/open_redirs.c) | C | 49 | 11 | 6 | 66 |
| [macrochibre/exec/pipes.c](/macrochibre/exec/pipes.c) | C | -5 | 0 | 0 | -5 |
| [macrochibre/get\_line/end\_get\_line.c](/macrochibre/get_line/end_get_line.c) | C | -10 | 0 | -1 | -11 |
| [macrochibre/get\_line/get\_line.h](/macrochibre/get_line/get_line.h) | C | 1 | 0 | 0 | 1 |
| [macrochibre/get\_line/history.c](/macrochibre/get_line/history.c) | C | 13 | 0 | 2 | 15 |
| [macrochibre/get\_line/line\_editing.c](/macrochibre/get_line/line_editing.c) | C | 0 | 0 | 1 | 1 |
| [macrochibre/get\_line/output\_editing.c](/macrochibre/get_line/output_editing.c) | C | 0 | 1 | 0 | 1 |
| [macrochibre/main.c](/macrochibre/main.c) | C | -45 | -11 | -9 | -65 |
| [macrochibre/minishell.h](/macrochibre/minishell.h) | C | 67 | 1 | 4 | 72 |
| [macrochibre/parsing/.get\_redir\_utils.c](/macrochibre/parsing/.get_redir_utils.c) | C | 1 | 53 | 7 | 61 |
| [macrochibre/parsing/.hdoc\_main.c](/macrochibre/parsing/.hdoc_main.c) | C | 44 | 11 | 2 | 57 |
| [macrochibre/parsing/.main.c](/macrochibre/parsing/.main.c) | C | 80 | 12 | 3 | 95 |
| [macrochibre/parsing/.redir\_main.c](/macrochibre/parsing/.redir_main.c) | C | 38 | 12 | 2 | 52 |
| [macrochibre/parsing/arg/get\_arg.c](/macrochibre/parsing/arg/get_arg.c) | C | -74 | -11 | -8 | -93 |
| [macrochibre/parsing/cmd\_funcs.c](/macrochibre/parsing/cmd_funcs.c) | C | 1 | 0 | 0 | 1 |
| [macrochibre/parsing/expand.c](/macrochibre/parsing/expand.c) | C | 42 | 11 | 7 | 60 |
| [macrochibre/parsing/get\_arg.c](/macrochibre/parsing/get_arg.c) | C | 69 | 11 | 8 | 88 |
| [macrochibre/parsing/get\_cmd\_line.c](/macrochibre/parsing/get_cmd_line.c) | C | 1 | 0 | 0 | 1 |
| [macrochibre/parsing/get\_hdoc.c](/macrochibre/parsing/get_hdoc.c) | C | 59 | 11 | 7 | 77 |
| [macrochibre/parsing/get\_redir.c](/macrochibre/parsing/get_redir.c) | C | 74 | 11 | 9 | 94 |
| [macrochibre/parsing/get\_redir\_name\_len.c](/macrochibre/parsing/get_redir_name_len.c) | C | 40 | 11 | 6 | 57 |
| [macrochibre/parsing/go\_to\_end\_of.c](/macrochibre/parsing/go_to_end_of.c) | C | 4 | 0 | 1 | 5 |
| [macrochibre/parsing/hdoc/get\_hdoc.c](/macrochibre/parsing/hdoc/get_hdoc.c) | C | -58 | -54 | -7 | -119 |
| [macrochibre/parsing/parsing\_utils.c](/macrochibre/parsing/parsing_utils.c) | C | 1 | 0 | 0 | 1 |
| [macrochibre/parsing/parsing\_utils2.c](/macrochibre/parsing/parsing_utils2.c) | C | 1 | 0 | 1 | 2 |
| [macrochibre/parsing/parsing\_utils3.c](/macrochibre/parsing/parsing_utils3.c) | C | 11 | 0 | 2 | 13 |
| [macrochibre/parsing/redir/get\_redir.c](/macrochibre/parsing/redir/get_redir.c) | C | -73 | -11 | -10 | -94 |
| [macrochibre/parsing/redir/get\_redir\_name\_len.c](/macrochibre/parsing/redir/get_redir_name_len.c) | C | -39 | -11 | -6 | -56 |
| [macrochibre/parsing/redir/get\_redir\_utils.c](/macrochibre/parsing/redir/get_redir_utils.c) | C | -1 | -53 | -7 | -61 |
| [macrochibre/parsing/test\_area/check\_line\_parsing.c](/macrochibre/parsing/test_area/check_line_parsing.c) | C | -54 | -11 | -4 | -69 |
| [macrochibre/parsing/var/.main.c](/macrochibre/parsing/var/.main.c) | C | -56 | -11 | -4 | -71 |
| [macrochibre/parsing/var/expand.c](/macrochibre/parsing/var/expand.c) | C | -42 | -11 | -6 | -59 |
| [macrochibre/parsing/var/var\_utils.c](/macrochibre/parsing/var/var_utils.c) | C | -15 | -11 | -5 | -31 |
| [macrochibre/parsing/var\_utils.c](/macrochibre/parsing/var_utils.c) | C | 15 | 11 | 5 | 31 |

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details