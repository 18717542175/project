package com.dao;

import com.bean.Iot;

import java.sql.SQLException;

public interface IotDAO {

    /**
     * 保存数据到数据库
     * @param iot
     * @return
     */
    public int saveIotData(Iot iot) throws SQLException;
}
