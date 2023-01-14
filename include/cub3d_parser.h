#ifndef CUB3D_PARSER_H
#define CUB3D_PARSER_H

#define _TEX_NBR 4

#ifdef BONUS
#define MAP_CHAR " 01SEWND"
#else
#define MAP_CHAR " 01SEWN"
#endif

#ifdef BONUS
#define MAP_OBJ_CHAR "01NSEW D"
#else
#define MAP_OBJ_CHAR "01NSEW "
#endif

// 向き
#define MAP_ORIENT_CHAR "SEWN"
#define FOUND 0
// 色データ長さ
#define COLOR_MAX_LEN 11
#define NBR_PARSING_ERR 11
// バッファ
#define PARSER_BUFFER_SIZE 8192
// マップ長さ最大
#define MAP_MAX_LENGH 8192
#define MAP_MAX_HEIGHT 8192
// 向き
#define DIR 1.0
// カメラ平面
#define CAM_PLANE 0.66
// 位置？
#define X_ADJUST 0.5
#define Y_ADJUST 0.5
#define MAX_PATH_LENGH 800

// エラー
#define MS_MLX_INIT "1: mlx_init failed!\n"
#define MS_MLX_RESOLUTION "2: the screen resolution is too low!\n"
#define MS_MLX_NEW_IMG "3: mlx_new_image failed!\n"
#define MS_MLX_NEW_WIN "4: mlx_new_window failed!\n"

#define MS_BLK_ERR "blocking error"
#define MS_NO_FILE "path to map is missing\n"
#define MS_EXTENTION "invalid extention\n"
#define MS_FOLDER "expecting : file.cut but received : directory.cub\n"
#define MS_CHMOD "access denied\n"
#define MS_PATH "path seems incorrect\n"
#define MS_EMPTY_FILE "	: map seems to be empty\n"
#define MS_TX_KEY_MISS "	: one or more texture path missing\n"
#define MS_TX_PATH "	: texture path seems incorrect\n"
#define MS_TX_PATH_LENGH "	: path too long\n"
#define MS_FC_OVERFLOW "	: colors value cannot exceed 255 or wrong format\n"
#define MS_FC_KEY_MISS "	: one or more color missing\n"
#define MS_FC_FORM "	: expected color format : F/C 255,255,255\n"
#define MS_MP_MISPLACED "	: map misplaced\n"
#define MS_MP_TOO_SMALL "	: no map / map is too small\n"
#define MS_MP_NO_PLAYER "	: a player is needed in the map\n"
#define MS_MP_MULTI_PLAYER "	: found more than one player in the map\n"
#define MS_MP_CUTTED "	: map cannot be cut\n"
#define MS_MP_BORDERS "	: incorrect map borders\n"
#define MS_MP_TOO_BIG "	: map is too big\n"
#define MS_MP_UNABLE_TO_CPY "	: impossible to copy map\n"
#define MS_GIBBER "	: found gibberish in infile\n"
#define MS_FC_MULTIDEF "	: re-definition of colors ignored\n"
#define MS_TX_MULTIDEF "	: re-definition of texture ignored\n"

// ファイルエラー
enum e_file_err
{
    ERR_NO_FILE,
    ERR_EXTENTION,
    ERR_FOLDER,
    ERR_CHMOD,
    ERR_PATH,
};

// マップエラー
enum e_map_err
{
    ERR_EMPTY_FILE,
    ERR_TX_KEY_MISS,
    ERR_TX_PATH,
    ERR_TX_PATH_LENGH,
    ERR_FC_OVERFLOW,
    ERR_FC_KEY_MISS,
    ERR_FC_FORM,
    ERR_MP_MISPLACED,
    ERR_MP_TOO_SMALL,
    ERR_MP_NO_PLAYER,
    ERR_MP_MULTI_PLAYER,
    ERR_MP_CUTTED,
    ERR_MP_BORDERS,
    ERR_MP_TOO_BIG,
    ERR_MP_UNABLE_TO_CPY,
    ERR_GIBBER,
    ERR_FC_MULTIDEF,
    ERR_TX_MULTIDEF,
};

// マップのデータ種類
enum e_line_type
{
    TYPE_NO,
    TYPE_SO,
    TYPE_WE,
    TYPE_EA,
    TYPE_F,
    TYPE_C,
    TYPE_MAP,
    TYPE_ERR,
    TYPE_USELESS,
    TYPE_EOF,
};

//
enum e_err_buf_index
{
    LINE_NBR,
    ERROR_CODE,
};

//
enum e_tab_free_opt
{
    NO_INDEX,
    WITH_INDEX,
};

// map解析用の構造体
typedef struct s_parser
{
    // 読み込んだ行
    char *line;
    // 読み込んだ行
    int gnl_cnt;
    // mapの最大x
    int map_max_x;
    // mapの最大y
    int map_max_y;
    // 読み込んだ行の種類
    int type;
    // 詳細情報のバッファ？色情報など、ファイルパスなど
    char info_buf[6][MAX_PATH_LENGH];
    // 画像データや色情報の詳細情報
    int info_buf_line[6];
    // mapデータ
    char *map_buf[PARSER_BUFFER_SIZE];
    // mapの読み込んだ行の行数
    int map_line_buf[PARSER_BUFFER_SIZE];
    // エラー行とメッセージを格納する
    int err_buf[PARSER_BUFFER_SIZE][2];
    // 詳細情報bit
    int info_buf_flag;
    // mapとerrのインデックス
    int map_buf_index;
    int err_buf_index;
    // 中断するエラーbit
    int blocking_err_flag;
} t_parser;

#endif