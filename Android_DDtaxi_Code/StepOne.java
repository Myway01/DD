package com.rd.callcar;

import com.baidu.mapapi.BMapManager;
import com.baidu.mapapi.GeoPoint;
import com.baidu.mapapi.LocationListener;
import com.baidu.mapapi.MapActivity;
import com.baidu.mapapi.MapController;
import com.baidu.mapapi.MapView;
import com.baidu.mapapi.MyLocationOverlay;
import com.rd.callcar.Util.DialogManager;
import com.rd.callcar.Util.ExitApplication;
import com.rd.callcar.Util.UpdateCustomer;
import com.rd.callcar.adapter.SettingAdapter;
import com.rd.callcar.data.staticData;
import com.rd.callcar.json.getJson;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.location.Location;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.ListView;
import android.widget.PopupWindow;
import android.widget.TextView;
import android.widget.Toast;

public class StepOne extends MapActivity {

	MapView mMapView = null;
	LocationListener mLocationListener = null;// onResumeʱע���listener��onPauseʱ��ҪRemove
	MyLocationOverlay mLocationOverlay = null; // ��λͼ��

	String cityName;
	MapController mMapController;

	EditText input_address;

	final int getAddSuccess = 0;
	final int getAddFail = 1;

	Button nextStep, back, local;
	TextView loadText;

	App app;

	PopupWindow popup;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		ExitApplication.getInstance().addActivity(this);

		new UpdateCustomer(this, false).Lgoining();

		app = (App) this.getApplication();
		if (app.mBMapMan == null) {
			app.mBMapMan = new BMapManager(getApplication());
			app.mBMapMan.init(app.mStrKey, new App.MyGeneralListener());
		}
		app.mBMapMan.start();
		// ���ʹ�õ�ͼSDK�����ʼ����ͼActivity
		super.initMapActivity(app.mBMapMan);

		mMapView = (MapView) findViewById(R.id.bmapView);
		mMapView.setBuiltInZoomControls(true);
		// ���������Ŷ���������Ҳ��ʾoverlay,Ĭ��Ϊ������
		mMapView.setDrawOverlayWhenZooming(true);
		mMapView.setBuiltInZoomControls(true);
		// ��ʼ������ģ�飬ע���¼�����
		mMapController = mMapView.getController(); // �õ�mMapView�Ŀ���Ȩ,�����������ƺ�����ƽ�ƺ�����
		GeoPoint point = new GeoPoint((int) (39.915 * 1E6),
				(int) (116.404 * 1E6)); // �ø����ľ�γ�ȹ���һ��GeoPoint����λ��΢�� (�� * 1E6)
		mMapController.setCenter(point); // ���õ�ͼ���ĵ�
		mMapController.setZoom(18); // ���õ�ͼzoom����

		// ��Ӷ�λͼ��
		mLocationOverlay = new MyLocationOverlay(this, mMapView);
		mMapView.getOverlays().add(mLocationOverlay);

		// ע�ᶨλ�¼�
		mLocationListener = new LocationListener() {

			@Override
			public void onLocationChanged(Location location) {
				if (location != null) {
					GeoPoint pt = new GeoPoint(
							(int) (location.getLatitude() * 1e6),
							(int) (location.getLongitude() * 1e6));
					mMapView.getController().animateTo(pt);

					final double lang = location.getLatitude();
					final double lant = location.getLongitude();

					input_address.setText(R.string.loadingAdd);
					loadText.setVisibility(View.VISIBLE);
					new Thread(new Runnable() {

						@Override
						public void run() {
							try {
								String add = getJson.getAddress(lang, lant,
										StepOne.this);
								if (add != "") {
									Message message = new Message();
									message.what = getAddSuccess;
									message.obj = add;
									handler.sendMessage(message);
								} else {
									Message message = new Message();
									message.what = getAddFail;
									handler.sendMessage(message);
								}
							} catch (Exception e) {
								Message message = new Message();
								message.what = getAddFail;
								handler.sendMessage(message);
							}
						}
					}).start();
				}
			}
		};

		input_address = (EditText) findViewById(R.id.input_address);

		nextStep = (Button) findViewById(R.id.nextStep);
		nextStep.setOnClickListener(new OnClick());

		back = (Button) findViewById(R.id.back);
		back.setOnClickListener(new OnClick());

		loadText = (TextView) findViewById(R.id.loadText);

		local = (Button) findViewById(R.id.local);
		local.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				app.mBMapMan.getLocationManager().requestLocationUpdates(
						mLocationListener);
				mLocationOverlay.enableMyLocation();
			}
		});
	}

	private Handler handler = new Handler() {

		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			switch (msg.what) {
			case getAddFail:
				loadText.setText("��λʧ�ܣ����Ժ����ԣ�");
				input_address.setText(R.string.loadAddFail);
				break;
			case getAddSuccess:
				mMapView.setVisibility(View.VISIBLE);
				loadText.setVisibility(View.GONE);
				input_address.setText((String) msg.obj);
				break;
			}
		}
	};

	class OnClick implements OnClickListener {
		@Override
		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.nextStep:
				if (!app.getLogin()) {
					startActivity(new Intent(StepOne.this, Login.class));
				} else {
					String beignStr = input_address.getText().toString().trim();
					if (beignStr.equals("")
							|| beignStr.equals(R.string.loadingAdd)
							|| beignStr.equals(R.string.loadAddFail)) {
						ShowToast(R.string.beginErr);
					} else {
						SaveBegin(beignStr);
						startActivity(new Intent(StepOne.this, StepTwo.class));
					}
				}
				break;
			case R.id.back:
				ShowPop();
				break;
			}
		}
	}

	private void ShowPop() {
		View view = getLayoutInflater().inflate(R.layout.pop_window2, null);
		LinearLayout tan = (LinearLayout) view.findViewById(R.id.tan);
		ListView settingList = (ListView) view.findViewById(R.id.settingList);
		SettingAdapter adapter = new SettingAdapter(this,
				staticData.getSettingList());
		settingList.setAdapter(adapter);
		settingList.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				if (popup != null) {
					if (popup.isShowing()) {
						popup.dismiss();
					}
				}

				if (!app.getLogin()) {
					startActivity(new Intent(StepOne.this, Login.class));
				} else {
					switch (arg2) {
					case 0:
						startActivity(new Intent(StepOne.this, Login.class));
						break;
					case 1:
						startActivity(new Intent(StepOne.this, Register.class));
						break;
					case 2:
						startActivity(new Intent(StepOne.this, CallRecord.class));
						break;
					case 3:
						startActivity(new Intent(StepOne.this,
								SettingActivity.class));
						break;
					case 4:
						app.SaveLogin(false);
						startActivity(new Intent(StepOne.this, Login.class));
						break;
					case 5:
						new DialogManager().showExitHit(StepOne.this);
						break;
					}
				}
			}
		});

		popup = new PopupWindow(view, LayoutParams.WRAP_CONTENT,
				LayoutParams.WRAP_CONTENT);
		popup.setFocusable(true);
		popup.setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
		popup.update();

		if (popup != null) {
			if (popup.isShowing())
				popup.dismiss();
			else {
				popup.showAsDropDown(findViewById(R.id.back), 0, 0);
			}
		}

		tan.setOnKeyListener(new OnKeyListener() {

			public boolean onKey(View v, int keyCode, KeyEvent event) {
				if (event.getAction() == KeyEvent.ACTION_DOWN
						&& keyCode == KeyEvent.KEYCODE_BACK) {
					if (popup != null) {
						if (popup.isShowing()) {
							popup.dismiss();
						}
					}
				}
				return false;
			}
		});
	}

	private void SaveBegin(String begin) {
		PreferenceManager.getDefaultSharedPreferences(getApplicationContext())
				.edit().putString("begin", begin).commit();
	}

	private void ShowToast(int res) {
		Toast.makeText(this, res, Toast.LENGTH_SHORT).show();
	}

	@Override
	protected void onPause() {
		App app = (App) this.getApplication();
		app.mBMapMan.getLocationManager().removeUpdates(mLocationListener);
		mLocationOverlay.disableMyLocation();
		// mLocationOverlay.disableCompass(); // �ر�ָ����
		app.mBMapMan.stop();
		super.onPause();
	}

	@Override
	protected void onResume() {
		App app = (App) this.getApplication();
		// ע�ᶨλ�¼�����λ�󽫵�ͼ�ƶ�����λ��
		app.mBMapMan.getLocationManager().requestLocationUpdates(
				mLocationListener);
		mLocationOverlay.enableMyLocation();
		// mLocationOverlay.enableCompass(); // ��ָ����
		app.mBMapMan.start();
		super.onResume();
	}

	@Override
	protected boolean isRouteDisplayed() {
		return false;
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
