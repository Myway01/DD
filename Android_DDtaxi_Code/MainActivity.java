package com.rd.callcar;

import com.rd.callcar.Util.DialogManager;
import com.rd.callcar.Util.ExitApplication;
import com.rd.callcar.Util.UpdateCustomer;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
	Button button_set, button_record, button_next;
	App app = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main_layout);
		ExitApplication.getInstance().addActivity(this);

		app = (App) getApplication();

		new UpdateCustomer(this, false).Lgoining();

		button_set = (Button) findViewById(R.id.button_set);
		button_record = (Button) findViewById(R.id.button_record);
		button_next = (Button) findViewById(R.id.button_next);

		button_set.setOnClickListener(new OnClk());
		button_record.setOnClickListener(new OnClk());
		button_next.setOnClickListener(new OnClk());
	}

	class OnClk implements OnClickListener {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.button_set:
				if (app.getLogin()) {
					startActivity(new Intent(MainActivity.this,
							SettingActivity.class));
				} else {
					startActivity(new Intent(MainActivity.this, Login.class));
				}
				break;
			case R.id.button_record:
				if (app.getLogin()) {
					startActivity(new Intent(MainActivity.this,
							CallRecord.class));
				} else {
					startActivity(new Intent(MainActivity.this, Login.class));
				}
				break;
			case R.id.button_next:
				if (app.getLogin()) {
					startActivity(new Intent(MainActivity.this, StepOne.class));
				} else {
					startActivity(new Intent(MainActivity.this, Login.class));
				}
				break;
			}
		}
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			new DialogManager().showExitHit(this);
			return false;
		}
		return super.onKeyDown(keyCode, event);
	}
}
