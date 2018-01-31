package org.speedcc.lib;


import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.Configuration;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.text.DateFormatSymbols;

public class JNISystem {

    public static int getOrientation(){
        switch(Cocos2dxActivity.getContext().getResources().getConfiguration().orientation)
        {
            case Configuration.ORIENTATION_LANDSCAPE: return 3;
            case Configuration.ORIENTATION_PORTRAIT: return 1;
            default: return 0;
        }
    }

    public static String getMonthName(int month,boolean isShort){

        DateFormatSymbols dfs = new DateFormatSymbols();
        String[] months = isShort ? dfs.getShortMonths() : dfs.getMonths();

        String ret = "";
        if(month>0 && month<13){
            ret = months[month-1];
        }
        return ret;
    }

    public static String getWeekName(int week,boolean isShort){

        DateFormatSymbols dfs = new DateFormatSymbols();
        String[] weeks = isShort ? dfs.getShortWeekdays() : dfs.getWeekdays();

        String ret = "";
        if(week>0 && week<8){
            ret = weeks[week];
        }
        return ret;
    }


    public static String getPackageName(){

        return Cocos2dxActivity.getContext().getPackageName();
    }

    public static String getProductName(){
        PackageManager packageManager = Cocos2dxActivity.getContext().getPackageManager();
        ApplicationInfo applicationInfo = null;
        try {
            applicationInfo = packageManager.getApplicationInfo(Cocos2dxActivity.getContext().getApplicationInfo().packageName, 0);
        } catch (final PackageManager.NameNotFoundException e) {
        }
        return (String) (applicationInfo != null ? packageManager.getApplicationLabel(applicationInfo) : "Unknown");
    }

    public static String getAppVersion(){
        try{
            PackageInfo pInfo = Cocos2dxActivity.getContext().getPackageManager().getPackageInfo(Cocos2dxActivity.getContext().getPackageName(), 0);
            return pInfo.versionName;
        }
        catch(Exception e){
            return "";
        }
    }

}
