package com.utils;

import com.alibaba.druid.pool.DruidDataSourceFactory;

import javax.sql.DataSource;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.SQLException;
import java.util.Properties;

public class JdbcUtils {

    private static DataSource source;
    private static DataSource iotSource;

    /**
     * 静态方法随着类的加载而加载 用于创建数据库连接池
     */
    static {
        try {
            //Properties用于读取配置文件的类
            Properties pros = new Properties();
            Properties iotPros = new Properties();
            //获取输入流 解析配置文件
            InputStream is = com.utils.JdbcUtils.class.getClassLoader().getResourceAsStream("druid.properties");
            InputStream iot = com.utils.JdbcUtils.class.getClassLoader().getResourceAsStream("iot.properties");

            pros.load(is);
            iotPros.load(iot);

            source = DruidDataSourceFactory.createDataSource(pros);
            iotSource = DruidDataSourceFactory.createDataSource(iotPros);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 连接用户数据库
     * @return conn 数据库连接对象
     * @throws SQLException
     */
    public static Connection getConnection() throws SQLException {
        Connection conn = source.getConnection();
        return conn;
    }

    /**
     * 连接用于存储数据的数据库
     * @return iotConn 数据库连接对象
     * @throws SQLException
     */
    public static Connection getIOTConnection() throws SQLException {
        Connection iotConn = iotSource.getConnection();
        return iotConn;
    }



//    @Test
//    public void test() throws SQLException {
//        Connection connection = getConnection();
//        close(connection);
//    }

    /**
     * 关闭连接 放回数据库连接池
     * @param conn
     */
    public static void close(Connection conn){
        if(conn != null)
        {
            try {
                conn.close();
                System.out.println("关闭成功！");
            }catch (Exception e)
            {
                System.out.println("未关闭！");
                e.printStackTrace();
            }
        }
    }
}
