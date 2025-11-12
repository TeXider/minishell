# Diff Details

Date : 2025-11-11 10:48:07

Directory /home/tpanou-d/Documents/github/minishell/macrochibre

Total : 42 files,  1216 codes, 379 comments, 157 blanks, all 1752 lines

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [dr\_mizumis\_lab/get\_line/.main.c](/dr_mizumis_lab/get_line/.main.c) | C | -27 | -20 | -4 | -51 |
| [dr\_mizumis\_lab/get\_line/create\_error.c](/dr_mizumis_lab/get_line/create_error.c) | C | -35 | -11 | -5 | -51 |
| [dr\_mizumis\_lab/get\_line/get\_line.c](/dr_mizumis_lab/get_line/get_line.c) | C | -176 | -13 | -21 | -210 |
| [dr\_mizumis\_lab/get\_line/get\_line.h](/dr_mizumis_lab/get_line/get_line.h) | C | -91 | -11 | -11 | -113 |
| [dr\_mizumis\_lab/get\_line/get\_line\_utils.c](/dr_mizumis_lab/get_line/get_line_utils.c) | C | -45 | -17 | -9 | -71 |
| [dr\_mizumis\_lab/get\_line/line\_editing.c](/dr_mizumis_lab/get_line/line_editing.c) | C | -15 | -11 | -5 | -31 |
| [dr\_mizumis\_lab/get\_line/memory.c](/dr_mizumis_lab/get_line/memory.c) | C | -22 | -11 | -4 | -37 |
| [dr\_mizumis\_lab/get\_line/output\_editing.c](/dr_mizumis_lab/get_line/output_editing.c) | C | -54 | -12 | -8 | -74 |
| [macrochibre/create\_error.c](/macrochibre/create_error.c) | C | 29 | 11 | 5 | 45 |
| [macrochibre/exec/exec\_cmd\_line.c](/macrochibre/exec/exec_cmd_line.c) | C | 65 | 14 | 6 | 85 |
| [macrochibre/exec/pipes.c](/macrochibre/exec/pipes.c) | C | 55 | 11 | 6 | 72 |
| [macrochibre/get\_line/.main.c](/macrochibre/get_line/.main.c) | C | 35 | 20 | 4 | 59 |
| [macrochibre/get\_line/end\_get\_line.c](/macrochibre/get_line/end_get_line.c) | C | 47 | 11 | 7 | 65 |
| [macrochibre/get\_line/get\_line.c](/macrochibre/get_line/get_line.c) | C | 51 | 11 | 5 | 67 |
| [macrochibre/get\_line/get\_line.h](/macrochibre/get_line/get_line.h) | C | 44 | 11 | 5 | 60 |
| [macrochibre/get\_line/get\_line\_utils.c](/macrochibre/get_line/get_line_utils.c) | C | 32 | 11 | 10 | 53 |
| [macrochibre/get\_line/handle\_ctrl.c](/macrochibre/get_line/handle_ctrl.c) | C | 48 | 11 | 6 | 65 |
| [macrochibre/get\_line/handle\_keys.c](/macrochibre/get_line/handle_keys.c) | C | 75 | 11 | 8 | 94 |
| [macrochibre/get\_line/history.c](/macrochibre/get_line/history.c) | C | 48 | 11 | 6 | 65 |
| [macrochibre/get\_line/history\_utils.c](/macrochibre/get_line/history_utils.c) | C | 28 | 11 | 5 | 44 |
| [macrochibre/get\_line/line\_editing.c](/macrochibre/get_line/line_editing.c) | C | 56 | 11 | 9 | 76 |
| [macrochibre/get\_line/memory.c](/macrochibre/get_line/memory.c) | C | 43 | 11 | 5 | 59 |
| [macrochibre/get\_line/output\_editing.c](/macrochibre/get_line/output_editing.c) | C | 75 | 11 | 10 | 96 |
| [macrochibre/main.c](/macrochibre/main.c) | C | 45 | 11 | 9 | 65 |
| [macrochibre/memory.c](/macrochibre/memory.c) | C | 59 | 11 | 7 | 77 |
| [macrochibre/minishell.h](/macrochibre/minishell.h) | C | 159 | 25 | 16 | 200 |
| [macrochibre/parsing/arg/get\_arg.c](/macrochibre/parsing/arg/get_arg.c) | C | 74 | 11 | 8 | 93 |
| [macrochibre/parsing/cmd\_funcs.c](/macrochibre/parsing/cmd_funcs.c) | C | 16 | 11 | 4 | 31 |
| [macrochibre/parsing/get\_argv\_redirv.c](/macrochibre/parsing/get_argv_redirv.c) | C | 46 | 11 | 6 | 63 |
| [macrochibre/parsing/get\_cmd\_line.c](/macrochibre/parsing/get_cmd_line.c) | C | 77 | 11 | 7 | 95 |
| [macrochibre/parsing/go\_to\_end\_of.c](/macrochibre/parsing/go_to_end_of.c) | C | 56 | 11 | 5 | 72 |
| [macrochibre/parsing/hdoc/get\_hdoc.c](/macrochibre/parsing/hdoc/get_hdoc.c) | C | 58 | 54 | 7 | 119 |
| [macrochibre/parsing/parsing\_utils.c](/macrochibre/parsing/parsing_utils.c) | C | 28 | 11 | 7 | 46 |
| [macrochibre/parsing/parsing\_utils2.c](/macrochibre/parsing/parsing_utils2.c) | C | 34 | 11 | 6 | 51 |
| [macrochibre/parsing/parsing\_utils3.c](/macrochibre/parsing/parsing_utils3.c) | C | 18 | 11 | 3 | 32 |
| [macrochibre/parsing/redir/get\_redir.c](/macrochibre/parsing/redir/get_redir.c) | C | 73 | 11 | 10 | 94 |
| [macrochibre/parsing/redir/get\_redir\_name\_len.c](/macrochibre/parsing/redir/get_redir_name_len.c) | C | 39 | 11 | 6 | 56 |
| [macrochibre/parsing/redir/get\_redir\_utils.c](/macrochibre/parsing/redir/get_redir_utils.c) | C | 1 | 53 | 7 | 61 |
| [macrochibre/parsing/test\_area/check\_line\_parsing.c](/macrochibre/parsing/test_area/check_line_parsing.c) | C | 54 | 11 | 4 | 69 |
| [macrochibre/parsing/var/.main.c](/macrochibre/parsing/var/.main.c) | C | 56 | 11 | 4 | 71 |
| [macrochibre/parsing/var/expand.c](/macrochibre/parsing/var/expand.c) | C | 42 | 11 | 6 | 59 |
| [macrochibre/parsing/var/var\_utils.c](/macrochibre/parsing/var/var_utils.c) | C | 15 | 11 | 5 | 31 |

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details