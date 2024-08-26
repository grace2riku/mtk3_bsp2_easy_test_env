/*
 * sync_and_com_client.c
 *
 *  Created on: 2024/08/26
 *      Author: k-abe
 */
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "sync_and_com_provider.h"
#include "sync_and_com_client.h"

/* 固定長メモリプールの生成情報と関連データ */
LOCAL ID mpfid_response;
LOCAL T_CMPF cmpf_response = {
	.mpfatr = TA_TFIFO | TA_RNG3,	// メモリプール属性
	.mpfcnt = 10,	// ブロック数
	.blfsz = sizeof(T_RESPONSE_MSG),	// ブロックサイズ
};

/* メールボックスの生成情報と関連データ */
LOCAL ID mbxid_response;	// メールボックスID番号
LOCAL T_CMBX cmbx_response = {
	.mbxatr = TA_TFIFO | TA_MFIFO,	// メールボックス属性
};

LOCAL void sync_and_com_provider_task(INT stacd, void *exinf);
LOCAL ID tskid_provider;
LOCAL T_CTSK ctsk_provider = {				// Task creation information
	.itskpri	= 10,
	.stksz		= 1024,
	.task		= sync_and_com_provider_task,
	.tskatr		= TA_HLNG | TA_RNG3,
};

LOCAL void sync_and_com_provider_task(INT stacd, void *exinf) {
	T_RESPONSE_MSG *response_msg;
	T_REQUEST_MSG *request_msg;
	ER ercd;

	while (1) {
		// コマンド待ち
		ercd = tk_rcv_mbx(get_mbxid_request(), (T_MSG**)&request_msg, TMO_FEVR);
		if (ercd != E_OK) {

		}

		// レスポンスのメモリブロックの獲得
		ercd = tk_get_mpf(get_mpfid_response(), (void**)&response_msg, TMO_FEVR);
		if (ercd != E_OK) {

		}

		// コマンド解析// メッセージの作成
		switch(request_msg->cmd) {
			case CMD_GET_START_CODE:	// タスクの引数取得コマンド
				response_msg->ercd = E_OK;
				response_msg->stacd = stacd;
				break;
			default:	// コマンドなし
				response_msg->ercd = E_PAR;
				break;
		}

		// メッセージの送信
		ercd = tk_snd_mbx(get_mbxid_response(), (T_MSG*)response_msg);
		if (ercd != E_OK) {

		}

		// リクエストのメモリブロックの返却
		tk_rel_mpf(get_mpfid_request(), (void*)request_msg);
	}
}

ID get_mpfid_response() {
	return mpfid_response;
}

ID get_mbxid_response() {
	return mbxid_response;
}

ER create_sync_and_com_provider_resource() {
	ER ercd = E_OK;

	mpfid_response = tk_cre_mpf(&cmpf_response);	// 固定長メモリプールの生成
	mbxid_response = tk_cre_mbx(&cmbx_response);	// メールボックスの生成

	tskid_provider = tk_cre_tsk(&ctsk_provider);
	ercd = tk_sta_tsk(tskid_provider, 0x12345678);

	return ercd;
}
