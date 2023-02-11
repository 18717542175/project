package com.service;

import com.bean.Iot;

import java.sql.SQLException;

public interface IotServer {

    /**
     * 向数据库中添加数据
     * @param iot
     */
    public void insIotData(Iot iot) throws SQLException;
}
