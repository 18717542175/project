package com.test;

import com.bean.Iot;
import com.service.IotServerImpl;
import org.junit.Test;

import javax.servlet.ServletContext;
import java.sql.SQLException;

public class IotServerTest {

    IotServerImpl server = new IotServerImpl();
    @Test
    public void saveIotData() throws SQLException {
        server.insIotData(new Iot("2022-4-7","12","12","12","12","12"));
    }
}
