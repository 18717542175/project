package com.service;

import com.bean.Iot;
import com.dao.IotDAO;
import com.dao.IotDAOImpl;

import java.sql.SQLException;

public class IotServerImpl implements IotServer{
    private IotDAO iotDao = new IotDAOImpl();

    /**
     * 对数据进行保存
     * @param iot
     * @throws SQLException
     */
    @Override
    public void insIotData(Iot iot) throws SQLException {
        iotDao.saveIotData(iot);
    }
}
