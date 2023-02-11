$(function () {
  //定义变量 用于数据的存储
  var at="";
  var myId="";
  var myValue="";

  // 基于准备好的dom，初始化echarts实例
  var myChart1 = echarts.init(document.querySelector(".line2 .chart"));
  var myChart2 = echarts.init(document.querySelector(".bar2 .chart"));
  var myChart3 = echarts.init(document.querySelector(".ple2 .chart"));
  var myChart4 = echarts.init(document.querySelector(".bar .chart"));
  var myChart5 = echarts.init(document.querySelector(".line .chart"));
  var myChart6 = echarts.init(document.querySelector(".ple .chart"));


  var date1 = new Date();
  var base = +new Date(date1.getHours(), date1.getMinutes(), date1.getSeconds());
  var oneDay = 1;
  var date = [];

  var newData_N = [Math.random()];
  var newData_P = [Math.random()];
  var newData_k = [Math.random()];
  var newData_W = [Math.random()];
  var newData_S = [Math.random()];
  var lastData = " ";     //用于存储提取出来的数据
  var sign = "6";          //用于存储提取出来的数据标志
  var floatData;
  var now_N = new Date(base);
  var now_P = new Date(base);
  var now_K = new Date(base);
  var now_W = new Date(base);
  var now_S = new Date(base);

  //用来保存最后解析出来的数据（id,n,p,k,w,s）
  var iotData = ["-","-","-","-","-","-"];

  /**
   * 更新数据函数
   * @param shift  true 删除数组第一个元素
   * @param dataValue   传入的数据
   * @param sign        数据标志位
   */
  function addData_N(shift,dataValue) {
    now_N = [now_N.getHours(), now_N.getMinutes() + 1, now_N.getSeconds()].join('/');
    date.push(now_N);
    newData_N.push(dataValue);
    // newData_N.push(sign);
    /**
     * 用于区别数据类型
     * sign：标志
     * 1-氮  2-磷 3-钾 4-温度*0.1 5-湿度*0.01
     */

    if (shift) {
      //删除数组中的第一项
      date.shift();
      newData_N.shift();
    }

    now_N = new Date(+new Date(now_N) + oneDay);
  }
  function addData_P(shift,dataValue) {
    now_P = [now_P.getHours(), now_P.getMinutes() + 1, now_P.getSeconds()].join('/');
    date.push(now_P);
    newData_P.push(dataValue);
    // newData_N.push(sign);
    /**
     * 用于区别数据类型
     * sign：标志
     * 1-氮  2-磷 3-钾 4-温度*0.1 5-湿度*0.01
     */

    if (shift) {
      //删除数组中的第一项
      date.shift();
      newData_P.shift();
    }

    now_P = new Date(+new Date(now_P) + oneDay);
  }
  function addData_K(shift,dataValue) {
    now_K = [now_K.getHours(), now_K.getMinutes() + 1, now_K.getSeconds()].join('/');
    date.push(now_K);
    newData_k.push(dataValue);
    // newData_N.push(sign);
    /**
     * 用于区别数据类型
     * sign：标志
     * 1-氮  2-磷 3-钾 4-温度*0.1 5-湿度*0.01
     */

    if (shift) {
      //删除数组中的第一项
      date.shift();
      newData_k.shift();
    }

    now_K = new Date(+new Date(now_K) + oneDay);
  }
  function addData_W(shift,dataValue) {
    now_W = [now_W.getHours(), now_W.getMinutes() + 1, now_W.getSeconds()].join('/');
    date.push(now_W);
    newData_W.push(dataValue);
    // newData_N.push(sign);
    /**
     * 用于区别数据类型
     * sign：标志
     * 1-氮  2-磷 3-钾 4-温度*0.1 5-湿度*0.01
     */

    if (shift) {
      //删除数组中的第一项
      date.shift();
      newData_W.shift();
    }

    now_W = new Date(+new Date(now_W) + oneDay);
  }
  function addData_S(shift,dataValue) {
    now_S = [now_S.getHours(), now_S.getMinutes() + 1, now_S.getSeconds()].join('/');
    date.push(now_S);
    newData_S.push(dataValue);
    // newData_N.push(sign);
    /**
     * 用于区别数据类型
     * sign：标志
     * 1-氮  2-磷 3-钾 4-温度*0.1 5-湿度*0.01
     */

    if (shift) {
      //删除数组中的第一项
      date.shift();
      newData_S.shift();
    }

    now_S = new Date(+new Date(now_S) + oneDay);
  }

  for (var i = 1; i < 50; i++) {
    addData_N();
    addData_P();
    addData_W();
    addData_S();
    addData_K();
  }


  /*湿度*/
  var option1 = {
    tooltip: {
      trigger: 'axis',
      axisPointer: {
        type: 'cross',
        label: {
          backgroundColor: '#6a7985'
        }
      }
    },
    legend: {
      top:"0%",
      // data: ['一月', '二月', '三月', '四月', '五月'],
      textStyle: {
        color: "rgba(255,255,255,.5)",
        fontsize:"12"
      }
    },
    toolbox: {
      feature: {
        saveAsImage: {}
      }
    },
    grid: {
      left: '5%',
      top:"10%",
      right: '5%',
      bottom: '5%',
      containLabel: true
    },
    xAxis: [
      {
        type: 'category',
        boundaryGap: false,
        data: now_N,
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.2)"
          }
        }
      }
    ],
    yAxis: [
      {
        type: 'value',
        axisTick:{show:false},
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        },
        /*改变分割线的颜色*/
        splitLine: {
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        }
      },

    ],
    series: [
      {
        smooth:true,
        name: 'N含量',
        type: 'line',
        /*线条的样式*/
        lineStyle:{
          color:"#0184d5",
          width:1
        },
        // stack: 'Total'
        /*填充颜色*/
        areaStyle: {
          color:new echarts.graphic.LinearGradient(
              0,0,0,1,
              [
                {
                  offset:0,
                  color:"rgba(1,132,213,0.4)"
                  /*渐变色起始颜色*/
                },{
                offset: 0.8,
                color: "rgba(1,132,231,0.1)"
                /*渐变色结束颜色*/
              }
              ],
              false
          ),
          shadowColor:"rgba(0,0,0,0.1)"
        },
        symbol:'circle',
        symbolSize:4,
        showSymbol:false,
        emphasis: {
          focus: 'series'
        },
        data: newData_N
      },

    ]
  };
  var option2 = {
    tooltip: {
      trigger: 'axis',
      axisPointer: {
        type: 'cross',
        label: {
          backgroundColor: '#6a7985'
        }
      }
    },
    legend: {
      top:"0%",
      // data: ['一月', '二月', '三月', '四月', '五月'],
      textStyle: {
        color: "rgba(255,255,255,.5)",
        fontsize:"12"
      }
    },
    toolbox: {
      feature: {
        saveAsImage: {}
      }
    },
    grid: {
      left: '5%',
      top:"10%",
      right: '5%',
      bottom: '5%',
      containLabel: true
    },
    xAxis: [
      {
        type: 'category',
        boundaryGap: false,
        data: now_P,
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.2)"
          }
        }
      }
    ],
    yAxis: [
      {
        type: 'value',
        axisTick:{show:false},
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        },
        /*改变分割线的颜色*/
        splitLine: {
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        }
      },

    ],
    series: [
      {
        smooth:true,
        name: 'P含量',
        type: 'line',
        /*线条的样式*/
        lineStyle:{
          color:"#0184d5",
          width:1
        },
        // stack: 'Total'
        /*填充颜色*/
        areaStyle: {
          color:new echarts.graphic.LinearGradient(
              0,0,0,1,
              [
                {
                  offset:0,
                  color:"rgba(1,132,213,0.4)"
                  /*渐变色起始颜色*/
                },{
                offset: 0.8,
                color: "rgba(1,132,231,0.1)"
                /*渐变色结束颜色*/
              }
              ],
              false
          ),
          shadowColor:"rgba(0,0,0,0.1)"
        },
        symbol:'circle',
        symbolSize:4,
        showSymbol:false,
        emphasis: {
          focus: 'series'
        },
        data: newData_P
      },

    ]
  };

  /**
   *    k含量显示
   */
  var option3 = {
    tooltip: {
      trigger: 'axis',
      axisPointer: {
        type: 'cross',
        label: {
          backgroundColor: '#6a7985'
        }
      }
    },
    legend: {
      top:"0%",
      // data: ['一月', '二月', '三月', '四月', '五月'],
      textStyle: {
        color: "rgba(255,255,255,.5)",
        fontsize:"12"
      }
    },
    toolbox: {
      feature: {
        saveAsImage: {}
      }
    },
    grid: {
      left: '5%',
      top:"10%",
      right: '5%',
      bottom: '5%',
      containLabel: true
    },
    xAxis: [
      {
        type: 'category',
        boundaryGap: false,
        data: now_K,
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.2)"
          }
        }
      }
    ],
    yAxis: [
      {
        type: 'value',
        axisTick:{show:false},
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        },
        /*改变分割线的颜色*/
        splitLine: {
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        }
      },

    ],
    series: [
      {
        smooth:true,
        name: 'K含量',
        type: 'line',
        /*线条的样式*/
        lineStyle:{
          color:"#0184d5",
          width:1
        },
        // stack: 'Total'
        /*填充颜色*/
        areaStyle: {
          color:new echarts.graphic.LinearGradient(
              0,0,0,1,
              [
                {
                  offset:0,
                  color:"rgba(1,132,213,0.4)"
                  /*渐变色起始颜色*/
                },{
                offset: 0.8,
                color: "rgba(1,132,231,0.1)"
                /*渐变色结束颜色*/
              }
              ],
              false
          ),
          shadowColor:"rgba(0,0,0,0.1)"
        },
        symbol:'circle',
        symbolSize:4,
        showSymbol:false,
        emphasis: {
          focus: 'series'
        },
        data: newData_k
      },

    ]
    };
  var myColor = ["#1089E7", "#F57474", "#56D0E3", "#F8B448", "#8B78F6"];
  var option4 = {
    tooltip: {
      trigger: 'axis',
      axisPointer: {
        type: 'cross',
        label: {
          backgroundColor: '#6a7985'
        }
      }
    },
    legend: {
      top:"0%",
      // data: ['一月', '二月', '三月', '四月', '五月'],
      textStyle: {
        color: "rgba(255,255,255,.5)",
        fontsize:"12"
      }
    },
    toolbox: {
      feature: {
        saveAsImage: {}
      }
    },
    grid: {
      left: '5%',
      top:"10%",
      right: '5%',
      bottom: '5%',
      containLabel: true
    },
    xAxis: [
      {
        type: 'category',
        boundaryGap: false,
        data: now_W,
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.2)"
          }
        }
      }
    ],
    yAxis: [
      {
        type: 'value',
        axisTick:{show:false},
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        },
        /*改变分割线的颜色*/
        splitLine: {
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        }
      },

    ],
    series: [
      {
        smooth:true,
        name: '土壤温度',
        type: 'line',
        /*线条的样式*/
        lineStyle:{
          color:"#0184d5",
          width:1
        },
        // stack: 'Total'
        /*填充颜色*/
        areaStyle: {
          color:new echarts.graphic.LinearGradient(
              0,0,0,1,
              [
                {
                  offset:0,
                  color:"rgba(1,132,213,0.4)"
                  /*渐变色起始颜色*/
                },{
                offset: 0.8,
                color: "rgba(1,132,231,0.1)"
                /*渐变色结束颜色*/
              }
              ],
              false
          ),
          shadowColor:"rgba(0,0,0,0.1)"
        },
        symbol:'circle',
        symbolSize:4,
        showSymbol:false,
        emphasis: {
          focus: 'series'
        },
        data: newData_W
      },

    ]
  };
  var option5 = {
    tooltip: {
      trigger: 'axis',
      axisPointer: {
        type: 'cross',
        label: {
          backgroundColor: '#6a7985'
        }
      }
    },
    legend: {
      top:"0%",
      // data: ['一月', '二月', '三月', '四月', '五月'],
      textStyle: {
        color: "rgba(255,255,255,.5)",
        fontsize:"12"
      }
    },
    toolbox: {
      feature: {
        saveAsImage: {}
      }
    },
    grid: {
      left: '5%',
      top:"10%",
      right: '5%',
      bottom: '5%',
      containLabel: true
    },
    xAxis: [
      {
        type: 'category',
        boundaryGap: false,
        data: now_S,
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.2)"
          }
        }
      }
    ],
    yAxis: [
      {
        type: 'value',
        axisTick:{show:false},
        axisLabel:{
          textStyle:{
            color:"rgba(255,255,255,.6)",
            fontsize:"12"
          }
        },
        /*x轴线的颜色*/
        axisLine:{
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        },
        /*改变分割线的颜色*/
        splitLine: {
          lineStyle:{
            color:"rgba(255,255,255,.1)"
          }
        }
      },

    ],
    series: [
      {
        smooth:true,
        name: '土壤湿度',
        type: 'line',
        /*线条的样式*/
        lineStyle:{
          color:"#0184d5",
          width:1
        },
        // stack: 'Total'
        /*填充颜色*/
        areaStyle: {
          color:new echarts.graphic.LinearGradient(
              0,0,0,1,
              [
                {
                  offset:0,
                  color:"rgba(1,132,213,0.4)"
                  /*渐变色起始颜色*/
                },{
                offset: 0.8,
                color: "rgba(1,132,231,0.1)"
                /*渐变色结束颜色*/
              }
              ],
              false
          ),
          shadowColor:"rgba(0,0,0,0.1)"
        },
        symbol:'circle',
        symbolSize:4,
        showSymbol:false,
        emphasis: {
          focus: 'series'
        },
        data: newData_S
      },

    ]
  };
  var option6 = {
    tooltip: {
      trigger: 'item',
      formatter: '{a} <br/>{b} : {c} ({d}%)'
    },
    legend: {
      left: '12',
      orient:"vertical",
      itemWidth:12,
      itemHeight:12,
      /*图例组件文字风格*/
      textStyle:{
        color:"rgba(255,255,255,.5)",
        fontsize:"12"
      }
    },
    toolbox: {
      show: true,
      feature: {
        mark: { show: true },
        // dataView: { show: true, readOnly: false },
        // restore: { show: true },
        saveAsImage: { show: true }
      }
    },
    series: [
      {
        name: '收入',
        type: 'pie',
        radius: [10, 100],
        center: ['60%', '60%'],
        roseType: 'radius',
        itemStyle: {
          borderRadius: 20
        },
        label: {
          show: false
        },
        emphasis: {
          label: {
            show: true
          }
        },
        data: [
          { value: 40, name: '石榴' },
          { value: 33, name: '苹果' },
          { value: 22, name: '梨' },
          { value: 20, name: '其他' }
        ]
      }
    ]
  };

  myChart1.setOption(option1);
  myChart2.setOption(option2,true);
  myChart3.setOption(option3);
  myChart4.setOption(option4);
  myChart5.setOption(option5);
  myChart6.setOption(option6);


  window.addEventListener("resize", function () {
    myChart1.resize();
  });
  window.addEventListener('resize', function () {
    myChart2.resize();
  })
  window.addEventListener("resize", function () {
    myChart3.resize();
  });
  window.addEventListener("resize", function() {
    myChart4.resize();
  });
  window.addEventListener("resize", function() {
    myChart5.resize();
  });
  window.addEventListener("resize", function () {
    myChart6.resize();
  });


  $(".update").click(function () {
    setInterval(func, 250);//定时更新数据
    /**
     * 检测到更新命令之后 发送ajax请求来获取数据
     */
    function func() {
      //绑定按钮点击事件

        $.ajax({
          url: "chartServlet",
          type: "GET",
          data: {
            "at": at,
            "id": myId,
            "value": myValue
          },
          dataType: "json",
          success: function (data) {
            //sign为数据的标志位 表示数据的类型
            //lastData表示实际传过来的数据值
            //eg：abcde中a：1-氮  2-磷 3-钾 4-温度*0.1 5-湿度*0.01
            sign = data.value.toString().substring(0,1);
            lastData = data.value.toString().substring(1,5);
            // alert(lastData);
            // 更新lastData数组中的数据
            if (sign == "1"){
              // console.log("1："+lastData);
              iotData[1] = lastData;
              addData_N(true,lastData);
            }else if (sign == "2"){
              // console.log("2："+lastData);
              iotData[2] = lastData;
              addData_P(true,lastData);
            }else if (sign == "3"){
              // console.log("3："+lastData);
              iotData[3] = lastData;
              addData_K(true,lastData);
            }else if (sign == "4"){
              // console.log("4："+lastData);
              floatData = parseFloat(lastData);
              floatData = floatData/10;
              iotData[4] = lastData;

              addData_W(true,floatData);
              // floatData = 0;
            }else if (sign == "5"){
              console.log("字符串5："+lastData);
              //此处将数据转换成小数
              floatData = parseFloat(lastData);
              floatData = floatData/100;
              console.log("浮点5："+floatData);
              iotData[5] = floatData;

              addData_S(true,floatData);
              // floatData = 0;
            }

            //更新图表数据
            myChart1.setOption({
              // xAxis: {
              //   data: date
              // },
              series: [{
                name:'N含量',
                data: newData_N
              }]
            });
            myChart2.setOption({
              // xAxis: {
              //   data: date
              // },
              series: [{
                name:'P含量',
                data: newData_P
              }]
            });
            myChart3.setOption({
              series: [{
                name:'K含量',
                data: newData_k
              }]
            });
            myChart4.setOption({
              // xAxis: {
              //   data: date
              // },
              series: [{
                name:'温度',
                data: newData_W
              }]
            });
            myChart5.setOption({
              series: [{
                name:'湿度',
                data: newData_S
              }]
            })

            // var time = date1.getMonth()+date1.getDay()+date1.getHours()+date1.getMinutes()+date1.getSeconds();
            var time = date1.toLocaleTimeString();
            iotData[0] = time.toString();
            console.log(time)

            var url = "chartServlet?id="+iotData[0]+"&n="+iotData[1]+"&p="+iotData[2]+"&k="+iotData[3]+"&w="+iotData[4]+"&s="+iotData[5]
            iotData[0] = null;
            //将解析的数据回传给Servlet
            $.ajax({
              type:"GET",
              url:url,
              success:function () {
                  console.log("数据回传完成："+ iotData);
              }
            })
          },
          error: function () {
            console.log("error");
          }
      })
    }
  })
});














