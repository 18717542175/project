package com.web;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.bean.Iot;
import com.service.IotServerImpl;
import org.json.JSONException;
import org.json.JSONObject;
import org.junit.runner.Request;


public class ChartServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        PrintWriter writer = resp.getWriter();
        IotServerImpl iotServer = new IotServerImpl();

        //获取js页面回传的iot数据
        Iot myIot = new Iot();
        myIot.setId(req.getParameter("id"));
        myIot.setN(req.getParameter("n"));
        myIot.setP(req.getParameter("p"));
        myIot.setK(req.getParameter("k"));
        myIot.setW(req.getParameter("w"));
        myIot.setS(req.getParameter("s"));
        System.out.println(myIot);

        try {
            //对数据进行保存
            if (myIot.getN() != null) {
                iotServer.insIotData(myIot);
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }


        String url = "http://api.heclouds.com/devices/datapoints?devIds=907044351";
        String api_key = "Ffm5zoe=kfmNTIzZscjg7gif2L0=";

        String result = parseJsonDataAndShow(doGet(url, api_key));

        writer.write(result);
//        System.out.println(result);
    }


    /**
     * Get请求
     * @param url  请求api
     * @param API_KEY    鉴权信息
     * @return
     */
    public static String doGet(String url,String API_KEY) {
        String result = "";

        BufferedReader reader = null;
        String boolJSONString = null;

        try {
            /*
             *   1.建立连接
             */
            //用于http请求的类 用于建立链接
            HttpURLConnection httpURLConnection = null;

            URL requestUrl = new URL(url);
            httpURLConnection = (HttpURLConnection) requestUrl.openConnection();
            httpURLConnection.setRequestMethod("GET");
            httpURLConnection.setConnectTimeout(8000);
            httpURLConnection.setRequestProperty("api-key", API_KEY);     //设置请求头内容

//            httpURLConnection.connect();        //连接会话
            /*
             * 2.获取二进制流
             * */
            InputStream inputStream = httpURLConnection.getInputStream();
            /*
             * 3.将二进制流包装成可理解的内容
             * */
            reader = new BufferedReader(new InputStreamReader(inputStream));
            /*
             * 4.从Buff...中读取String字符串
             *
             * */
            String line;
            StringBuilder builder = new StringBuilder();

            while ((line = reader.readLine()) != null) {
                builder.append(line);
                builder.append("\n");
            }

            if (builder.length() == 0) {
                return null;
            }

            result = builder.toString();

        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    /**
     * 对获取的json数据进行解析
     * @param jsonStr  json字符串
     * @return
     */
    public String parseJsonDataAndShow(String jsonStr) {
        List<String> Date = new ArrayList<>();
        String datapoints = null;
        //解析json数据
        try {
            //第一层解析
            JSONObject jsonObject1 = new JSONObject(jsonStr);
            String time = jsonObject1.optString("errno");
            String value1 = jsonObject1.optString("data");

            //第二层解析
            JSONObject jsonObject2 = new JSONObject(value1);
            String value2 = jsonObject2.optString("devices");
            //截取多余的字符
            value2 = value2.substring(1,value2.length()-1);

            //第三层解析
            JSONObject jsonObject3 = new JSONObject(value2);
            datapoints = jsonObject3.optString("datastreams");
            datapoints = datapoints.substring(1,datapoints.length()-1);

            //第四层解析
            JSONObject jsonObject4 = new JSONObject(datapoints);
            String at = jsonObject4.optString("at");
            String value = jsonObject4.optString("value");

            //将解析出来的数据保存到数据库

        } catch (JSONException e) {
            e.printStackTrace();
        }
        return datapoints;
    }
}
