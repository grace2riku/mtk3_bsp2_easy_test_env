/*
 * sync_and_com_provider.c
 *
 *  Created on: 2024/08/26
 *      Author: k-abe
 */
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "sync_and_com_client.h"

/* 固定長メモリプールの生成情報と関連データ */
LOCAL ID mpfid_request;
LOCAL T_CMPF cmpf_request = {
	.mpfatr = TA_TFIFO | TA_RNG3,	// メモリプール属性
	.mpfcnt = 10,	// ブロック数
	.blfsz = sizeof(T_REQUEST_MSG),	// ブロックサイズ
};

/* メールボックスの生成情報と関連データ */
LOCAL ID mbxid_request;	// メールボックスID番号
LOCAL T_CMBX cmbx_request = {
	.mbxatr = TA_TFIFO | TA_MFIFO,	// メールボックス属性
};

ID get_mpfid_request() {
	return mpfid_request;
}

ID get_mbxid_request() {
	return mbxid_request;
}

ER create_sync_and_com_client_resource() {
	ER ercd = E_OK;

	mpfid_request = tk_cre_mpf(&cmpf_request);	// 固定長メモリプールの生成
	mbxid_request = tk_cre_mbx(&cmbx_request);	// メールボックスの生成

	return ercd;
}
