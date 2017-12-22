package com.rd.callcar;

import com.rd.callcar.Util.ExitApplication;
import com.rd.callcar.Util.UpdateCustomer;
import com.rd.callcar.Util.getSystemInfo;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class SettingActivity extends Activity {

	private Button back, nameSet_button, pwdSet_button, jingYinSet_button,
			about_button;
	private TextView setName, versionName;
	private RelativeLayout updateRelative;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.setting_layout);
		ExitApplication.getInstance().addActivity(this);

		back = (Button) findViewById(R.id.back);
		nameSet_button = (Button) findViewById(R.id.nameSet_button);
		pwdSet_button = (Button) findViewById(R.id.pwdSet_button);
		jingYinSet_button = (Button) findViewById(R.id.jingYinSet_button);
		about_button = (Button) findViewById(R.id.about_button);

		setName = (TextView) findViewById(R.id.setName);
		versionName = (TextView) findViewById(R.id.versionName);

		updateRelative = (RelativeLayout) findViewById(R.id.updateRelative);

		back.setOnClickListener(new OnClk());
		nameSet_button.setOnClickListener(new OnClk());
		pwdSet_button.setOnClickListener(new OnClk());
		jingYinSet_button.setOnClickListener(new OnClk());
		about_button.setOnClickListener(new OnClk());

		updateRelative.setOnClickListener(new OnClk());

		ReadSetting();
	}

	private void ReadSetting() {

		// PreferenceManager
		// .getDefaultSharedPreferences(
		// getApplicationContext()).edit()
		// .putBoolean("isShow", isChecked).commit();

		setName.setText(PreferenceManager.getDefaultSharedPreferences(
				getApplicationContext()).getString("name", ""));

		pwdSet_button.setText(PreferenceManager.getDefaultSharedPreferences(
				getApplicationContext()).getBoolean("pwdset", false) ? "已设置>"
				: "未设置>");

		jingYinSet_button.setText(PreferenceManager
				.getDefaultSharedPreferences(getApplicationContext())
				.getBoolean("jingyin", false) ? "已开启" : "已关闭");

		versionName.setText("V"
				+ getSystemInfo.getVersionName(SettingActivity.this));
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (resultCode == 1) {
			setName.setText(data.getStringExtra("name"));
		}
		if (resultCode == 2) {
			pwdSet_button.setText(data.getStringExtra("back"));
		}
		super.onActivityResult(requestCode, resultCode, data);
	}

	class OnClk implements OnClickListener {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.back:
				SettingActivity.this.finish();
				break;
			case R.id.nameSet_button:
				startActivityForResult(new Intent(SettingActivity.this,
						NameSettingActivity.class), 1);
				break;
			case R.id.pwdSet_button:
				startActivityForResult(new Intent(SettingActivity.this,
						PwdSettingActivity.class), 2);
				break;
			case R.id.jingYinSet_button:
				if (PreferenceManager.getDefaultSharedPreferences(
						getApplicationContext()).getBoolean("jingyin", false)) {
					PreferenceManager
							.getDefaultSharedPreferences(
									getApplicationContext()).edit()
							.putBoolean("jingyin", false).commit();
				} else {
					PreferenceManager
							.getDefaultSharedPreferences(
									getApplicationContext()).edit()
							.putBoolean("jingyin", true).commit();
				}
				jingYinSet_button.setText(PreferenceManager
						.getDefaultSharedPreferences(getApplicationContext())
						.getBoolean("jingyin", false) ? "已开启" : "已关闭");
				break;
			case R.id.about_button:
				final AlertDialog alertDialog = new AlertDialog.Builder(
						SettingActivity.this)
						.setTitle(R.string.Hint)
						.setMessage(R.string.aboutContent)
						.setPositiveButton(R.string.sure,
								new DialogInterface.OnClickListener() {
									public void onClick(DialogInterface dialog,
											int which) {
									}
								}).create();
				alertDialog.show();
				break;
			case R.id.updateRelative:
				new UpdateCustomer(SettingActivity.this, true).Lgoining();
				break;
			}
		}
	}

}
