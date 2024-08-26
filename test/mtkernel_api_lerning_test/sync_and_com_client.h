#ifndef __SYNC_AND_COM_CLIENT_H
#define __SYNC_AND_COM_CLIENT_H

#include <tk/tkernel.h>
#include <tm/tmonitor.h>

/* コマンドの定義 */
#define CMD_GET_START_CODE (1)	// タスクの引数取得

/* メッセージの定義 */
typedef struct {
	T_MSG msgque;	// メッセージヘッダ(OSが使用)
	INT cmd;		// コマンド
} T_REQUEST_MSG;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern ER create_sync_and_com_client_resource();
extern ID get_mpfid_request();
extern ID get_mbxid_request();


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __SYNC_AND_COM_CLIENT_H
