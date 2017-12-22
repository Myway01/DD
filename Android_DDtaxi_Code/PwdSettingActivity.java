package com.rd.callcar;

import com.rd.callcar.Util.ExitApplication;
import com.rd.callcar.json.getJson;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class PwdSettingActivity extends Activity {

	private EditText oldPwdEdit, newPwdEdit, newsurePwdEdit;
	private Button save, back;

	App app = null;

	final int ChangePwdSUCCESS_MSG = 0;
	final int ChangePwdFAIL_MSG = 1;

	private ProgressDialog mpDialog;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.pwd_layout);
		ExitApplication.getInstance().addActivity(this);

		app = (App) getApplication();

		// 初始化加载对话框
		mpDialog = new ProgressDialog(this);
		mpDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		mpDialog.setTitle(R.string.pwdHint);
		mpDialog.setIcon(android.R.drawable.ic_dialog_info);
		mpDialog.setMessage(getString(R.string.saving));
		mpDialog.setIndeterminate(false);
		mpDialog.setCancelable(true);

		oldPwdEdit = (EditText) findViewById(R.id.oldPwdEdit);
		newPwdEdit = (EditText) findViewById(R.id.newPwdEdit);
		newsurePwdEdit = (EditText) findViewById(R.id.newsurePwdEdit);

		save = (Button) findViewById(R.id.save);
		save.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				ChangePwd();
			}
		});

		back = (Button) findViewById(R.id.back);
		back.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				PwdSettingActivity.this.finish();
			}
		});
	}

	private void ChangePwd() {
		final String oldPwd = oldPwdEdit.getText().toString().trim();
		final String newPwd = newPwdEdit.getText().toString().trim();
		String newPwdSure = newsurePwdEdit.getText().toString().trim();

		if (oldPwd.equals("")) {
			app.ShowToast(R.string.enterOldPwdHint);
			return;
		}

		if (newPwd.equals("")) {
			app.ShowToast(R.string.enterNewOwdHint);
			return;
		}

		if (!newPwdSure.equals(newPwd)) {
			app.ShowToast(R.string.pwdNoEqualHint);
			return;
		}

		if (newPwd.length() < 6) {
			app.ShowToast(R.string.noEnough);
			return;
		}

		if (newPwd.length() > 18) {
			app.ShowToast(R.string.noMore);
			return;
		}

//		if (!newPwd.matches("[a-zA-Z][a-zA-Z0-9]*")) {
//			app.ShowToast(R.string.pwdRegx);
//			return;
//		}

		final String userid = app.getUSerid();

		mpDialog.show();
		new Thread(new Runnable() {

			@Override
			public void run() {
				try {
					String back = getJson.ChangePwd(userid, oldPwd, newPwd);
					if (back != null) {
						Message message = new Message();
						message.what = ChangePwdSUCCESS_MSG;
						message.obj = userid;
						mhandler.sendMessage(message);
					} else {
						Message message = new Message();
						message.what = ChangePwdFAIL_MSG;
						mhandler.sendMessage(message);
					}
				} catch (Exception e) {
					Message message = new Message();
					message.what = ChangePwdFAIL_MSG;
					mhandler.sendMessage(message);
				}
			}
		}).start();
	}

	// 线程处理
	private Handler mhandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			mpDialog.dismiss();
			switch (msg.what) {
			case ChangePwdSUCCESS_MSG:
				app.ShowToast((String) msg.obj);
				PwdSettingActivity.this.setResult(2,
						new Intent().putExtra("back", "已设置>"));
				PreferenceManager
						.getDefaultSharedPreferences(getApplicationContext())
						.edit().putBoolean("pwdset", true).commit();
				PwdSettingActivity.this.finish();
				break;
			case ChangePwdFAIL_MSG:
				app.ShowToast(R.string.changePwdFail);
				PwdSettingActivity.this.finish();
				break;
			}
		}
	};

}
