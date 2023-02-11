apiready = function() {};

function randomSwitchBtn() {


    if (event.target.id == "contentN") {
        api.openWin({
            name: 'zhuye',
            url: 'echarts.html'
        })
    }
    if (event.target.id == "THcontent") {
        api.openWin({
            name: 'TH',
            url: 'T_h.html'
        })
    }

}