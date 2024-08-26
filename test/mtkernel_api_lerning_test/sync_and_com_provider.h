#ifndef __SYNC_AND_COM_PROVIDER_H
#define __SYNC_AND_COM_PROVIDER_H

/* メッセージの定義 */
typedef struct {
	T_MSG msgque;	// メッセージヘッダ(OSが使用)
	ER ercd;		// エラーコード
	INT stacd;		// タスク起動コード
} T_RESPONSE_MSG;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern ER create_sync_and_com_provider_resource();
extern ID get_mpfid_response();
extern ID get_mbxid_response();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __SYNC_AND_COM_PROVIDER_H
