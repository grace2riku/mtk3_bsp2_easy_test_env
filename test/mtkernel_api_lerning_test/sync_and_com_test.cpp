/*
 * sync_and_com_test.cpp
 *
 *  Created on: 2024/08/25
 *      Author: k-abe
 */
#include "CppUTest/TestHarness.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "sync_and_com_provider.h"
#include "sync_and_com_client.h"

TEST_GROUP(SyncAndComTestGroup)
{
	// TEST_GROUPの中の変数はTEST_GROUPで共有できる

    void setup()  // setupは各TEST実行の際に呼び出される
    {

    }

    void teardown()
    {
    }
};

TEST(SyncAndComTestGroup, BasicUsageMailbox)
{
	T_REQUEST_MSG *request_msg;
	T_RESPONSE_MSG *response_msg;
	ER ercd;

	// コマンドリクエストのメモリブロックの獲得
	ercd = tk_get_mpf(get_mpfid_request(), (void**)&request_msg, TMO_FEVR);
	if (ercd != E_OK) {
		FAIL("FAIL: SyncAndComTestGroup, BasicUsageMailbox tk_get_mpf");
	}

	// メッセージの作成
	request_msg->cmd = CMD_GET_START_CODE;	// タスクの引数取得コマンドを要求する

	// メッセージの送信
	ercd = tk_snd_mbx(get_mbxid_request(), (T_MSG*)request_msg);
	if (ercd != E_OK) {
		FAIL("FAIL: SyncAndComTestGroup, BasicUsageMailbox tk_snd_mbx");
	}

	// レスポンスのメッセージ受信待ち
	ercd = tk_rcv_mbx(get_mbxid_response(), (T_MSG**)&response_msg, TMO_FEVR);
	if (ercd != E_OK) {
		FAIL("FAIL: SyncAndComTestGroup, BasicUsageMailbox tk_rcv_mbx");
	}

	// レスポンスデータのチェック
	LONGS_EQUAL(E_OK, response_msg->ercd);
	LONGS_EQUAL(0x12345678, response_msg->stacd);

	// レスポンスのメモリブロックの返却
	tk_rel_mpf(get_mpfid_response(), (void*)response_msg);
}
