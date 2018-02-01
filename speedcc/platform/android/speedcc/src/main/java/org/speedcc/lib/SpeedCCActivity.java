package org.speedcc.lib;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import org.cocos2dx.lib.Cocos2dxActivity;

/**
 * Created by Kevin on 30/1/2018.
 */

public class SpeedCCActivity extends Cocos2dxActivity {

    private GooglePlayIAP mIAP;
    private static SpeedCCActivity mSpeedCCActivity;

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mSpeedCCActivity = this;
    }

    public static Activity getActivity(){
        return mSpeedCCActivity;
    }


    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        if(mIAP!=null){
            boolean result = mIAP.handleActivityResult(requestCode, resultCode, data );
            if (!result) {
                super.onActivityResult(requestCode, resultCode, data);
            }
        }

    }
}
