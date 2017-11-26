package com.rd.callcar;

import com.rd.callcar.Util.ExitApplication;
import com.rd.callcar.json.getJson;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class Login extends Activity {

	private Button login, register;
	private EditText input_userid, input_pwd;

	private ProgressDialog mpDialog;

	final int LOGINSUCCESS_MSG = 0;
	final int LOGINFAIL_MSG = 1;
	App app = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.login_layout);
		ExitApplication.getInstance().addActivity(this);

		app = (App) getApplication();

//		if (app.getLogin()) {
//			StartMain();
//		}

		// 初始化加载对话框
		mpDialog = new ProgressDialog(this);
		mpDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		mpDialog.setTitle(R.string.loading_data);
		mpDialog.setIcon(android.R.drawable.ic_dialog_info);
		mpDialog.setMessage(getString(R.string.waiting));
		mpDialog.setIndeterminate(false);
		mpDialog.setCancelable(true);

		login = (Button) findViewById(R.id.login);
		register = (Button) findViewById(R.id.register);

		input_userid = (EditText) findViewById(R.id.input_userid);
		input_pwd = (EditText) findViewById(R.id.input_pwd);

		login.setOnClickListener(new OnClick());
		register.setOnClickListener(new OnClick());
	}

	class OnClick implements OnClickListener {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.login:
				LoginMeth();
				break;
			case R.id.register:
				startActivityForResult(new Intent(Login.this, Register.class),
						1);
				break;
			}
		}
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == 1) {
			if (resultCode == 1) {
				input_userid.setText(data.getStringExtra("userid"));
			}
		}
		super.onActivityResult(requestCode, resultCode, data);
	}

	private void LoginMeth() {
		final String userid = input_userid.getText().toString().trim();
		final String pwd = input_pwd.getText().toString().trim();

		if (userid.equals("")) {
			ShowToast(R.string.noUserNameErr);
			return;
		}

		if (pwd.equals("")) {
			ShowToast(R.string.noPwdErr);
			return;
		}

		mpDialog.show();
		new Thread(new Runnable() {

			@Override
			public void run() {
				try {
					boolean isLogin = true;//getJson.Login(userid, pwd);
					if (isLogin) {
						Message message = new Message();
						message.what = LOGINSUCCESS_MSG;
						message.obj = userid;
						mhandler.sendMessage(message);
					} else {
						Message message = new Message();
						message.what = LOGINFAIL_MSG;
						mhandler.sendMessage(message);
					}
				} catch (Exception e) {
					Message message = new Message();
					message.what = LOGINFAIL_MSG;
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
			case LOGINSUCCESS_MSG:
				app.SaveBegin("userid", "18013398197");
				app.SaveLogin(true);
				StartMain();
				break;
			case LOGINFAIL_MSG:
				ShowToast(R.string.loginFail);
				break;
			}
		}
	};

	private void StartMain() {
		startActivity(new Intent(Login.this, StepOne.class));
		Login.this.finish();
	}

	private void ShowToast(int res) {
		Toast.makeText(this, res, Toast.LENGTH_SHORT).show();
	}
}
