package com.rd.callcar;

import com.rd.callcar.Util.ExitApplication;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Toast;

public class NameSettingActivity extends Activity {

	private Button back, save;
	private EditText xingEdit, mingEdit, nichenEdit;
	private CheckBox showTrueName;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.name_layout);
		ExitApplication.getInstance().addActivity(this);

		back = (Button) findViewById(R.id.back);
		save = (Button) findViewById(R.id.save);

		xingEdit = (EditText) findViewById(R.id.xingEdit);
		mingEdit = (EditText) findViewById(R.id.mingEdit);
		nichenEdit = (EditText) findViewById(R.id.nichenEdit);

		showTrueName = (CheckBox) findViewById(R.id.showTrueName);

		readSave();

		back.setOnClickListener(new OnClk());
		save.setOnClickListener(new OnClk());
	}

	private void readSave() {
		showTrueName.setChecked(PreferenceManager.getDefaultSharedPreferences(
				getApplicationContext()).getBoolean("showreadName", false));

		xingEdit.setText(PreferenceManager.getDefaultSharedPreferences(
				getApplicationContext()).getString("xing", ""));

		mingEdit.setText(PreferenceManager.getDefaultSharedPreferences(
				getApplicationContext()).getString("ming", ""));

		nichenEdit.setText(PreferenceManager.getDefaultSharedPreferences(
				getApplicationContext()).getString("nichen", ""));
	}

	class OnClk implements OnClickListener {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.back:
				NameSettingActivity.this.finish();
				break;
			case R.id.save:
				PreferenceManager
						.getDefaultSharedPreferences(getApplicationContext())
						.edit()
						.putBoolean("showreadName", showTrueName.isChecked())
						.commit();

				PreferenceManager
						.getDefaultSharedPreferences(getApplicationContext())
						.edit()
						.putString("xing", xingEdit.getText().toString())
						.commit();

				PreferenceManager
						.getDefaultSharedPreferences(getApplicationContext())
						.edit()
						.putString("ming", mingEdit.getText().toString())
						.commit();

				PreferenceManager
						.getDefaultSharedPreferences(getApplicationContext())
						.edit()
						.putString("nichen", nichenEdit.getText().toString())
						.commit();

				Toast.makeText(NameSettingActivity.this, "±£´æ³É¹¦£¡",
						Toast.LENGTH_SHORT).show();
				String name = showTrueName.isChecked() ? nichenEdit.getText()
						.toString() : xingEdit.getText().toString()
						+ mingEdit.getText().toString();

				PreferenceManager
						.getDefaultSharedPreferences(getApplicationContext())
						.edit().putString("name", name).commit();
				NameSettingActivity.this.setResult(1,
						new Intent().putExtra("name", name));
				NameSettingActivity.this.finish();
				break;
			}
		}
	}

}
