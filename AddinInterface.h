/*
///////////////////////////////////////////////////////////////////////////
金字塔“C++语言接口”调用接口规范V3.0
该项目使用MFC共享DLL创建的，编译后扩展名修改为adi文件，放在金字塔主目录下
重启金字塔后，在工具菜单->扩展二级菜单中,可以看到你的插件.

注意：
1、请在编译RELEASE版本运行插件，不要用DEBUG！
2、请注意金字塔的版本,如果是x64模式的金字塔版本,请将你的DLL也编译成64位版本才可以使用。

  'QS'上海期货市场,市场代码表示是一个WROD类型的,字符显示是 "SH", 到了WORD 就为 'HS'
  具体每个市场的代码在工具菜单->市场与板块中,查看市场的代号,设置和进行管理.
*/


#if !defined(__ADDININTERFACE_EX_H__)
#define __ADDININTERFACE_EX_H__

#define		STKLABEL_LEN			10			// 股号数据长度,国内市场股号编码兼容钱龙
#define		STKNAME_LEN				32			// 股名长度

#pragma pack (push ,1)

//动态行情数据结构
typedef struct	
{
	DWORD	m_time;										// 成交时间(time_t)
	
	float	m_fLastClose;								// 昨收
	float	m_fOpen;									// 今开
	float	m_fHigh;									// 最高
	float	m_fLow;										// 最低
	float	m_fNewPrice;								// 最新
	float	m_fOI;										//open interest
	float	m_fLastOI;
	float	m_fVolume;									// 成交量
	float	m_fAmount;									// 成交额
	
	float	m_fLastOpen;								//前开
	float	m_fLastHigh;								//前高
	float	m_fLastLow;									//前底
	
	float	m_fBuyPrice[3];								// 申买价1,2,3
	float	m_fBuyVolume[3];							// 申买量1,2,3
	float	m_fSellPrice[3];							// 申卖价1,2,3
	float	m_fSellVolume[3];							// 申卖量1,2,3
	
	float	m_fBuyPrice4;								// 申买价4
	float	m_fBuyVolume4;								// 申买量4
	float	m_fSellPrice4;								// 申卖价4
	float	m_fSellVolume4;								// 申卖量4
	
	float	m_fBuyPrice5;								// 申买价5
	float	m_fBuyVolume5;								// 申买量5
	float	m_fSellPrice5;								// 申卖价5
	float	m_fSellVolume5;								// 申卖量5
	
	float	m_fVolumeNow;								//现手
	float	m_fBuyVol;									//外盘量
	float	m_fSellVol;									//内盘量
	char	m_szName[32];								// 股票名称,以'\0'结尾
	char	m_szNamePY[16];
	char	m_szLabel[10];								// 股票代码,以'\0'结尾
	float   m_f5DayAverage;								//5日均量
	float	m_fNext5DayVol;								//下一个5日均量
	DWORD	m_timeHardenSpeed;							//涨速前比较时间
	float	m_fHardenSpeed;								//涨速用变量，记录前5分钟价格
	WORD	m_wMarket;									//品种所属市场比如上海'HS',深圳'ZS'
}REPORT_STRUCT;

//扩展动态行情数据结构
typedef struct 
{
	DWORD m_time;          // 成交时间
	
	float m_fLastClose;        // 昨收
	float m_fOpen;         // 今开
	float m_fHigh;         // 最高
	float m_fLow;          // 最低
	float m_fNewPrice;        // 最新
	float m_fOI;    //open interest
	float m_fLastOI;
	float m_fVolume;         // 成交量
	float m_fAmount;         // 成交额
	
	float m_fLastOpen;  //前开
	float m_fLastHigh;  //前高
	float m_fLastLow;   //前底
	
	float m_fBuyPrice[3];        // 申买价1,2,3
	float m_fBuyVolume[3];       // 申买量1,2,3
	float m_fSellPrice[3];       // 申卖价1,2,3
	float m_fSellVolume[3];       // 申卖量1,2,3
	
	float m_fBuyPrice4;        // 申买价4
	float m_fBuyVolume4;        // 申买量4
	float m_fSellPrice4;        // 申卖价4
	float m_fSellVolume4;        // 申卖量4
	
	float m_fBuyPrice5;        // 申买价5
	float m_fBuyVolume5;        // 申买量5
	float m_fSellPrice5;        // 申卖价5
	float m_fSellVolume5;        // 申卖量5
	
	float m_fVolumeNow;        //现手
	float m_fBuyVol;         //外盘量
	float m_fSellVol;         //内盘量
	char m_szName[32];      // 股票名称,以'\0'结尾
	char m_szNamePY[16];
	char m_szLabel[10];     // 股票代码,以'\0'结尾
	float   m_f5DayAverage;        //5日均量
	float m_fNext5DayVol;        //下一个5日均量
	DWORD m_timeHardenSpeed;       //涨速前比较时间
	float m_fHardenSpeed;        //涨速用变量，记录前5分钟价格
	WORD m_wMarket;
	
	float m_fBuyAmount;        //外盘额
	float m_fSellAmount;        //内盘额
	float m_fPoweru;         //买卖劲道
	float   m_fPowerd;
	WORD    m_nBuyBi;         //主买笔数
	WORD    m_nSellBi;
	float m_fAmountNow;        //现额
	WORD m_wBorNum;         //成交买卖单数
	WORD    m_wSorNum;
	BYTE m_nOrnumType;        //成交买卖方向 1主买 0主卖
	WORD m_wTickUp0;   //上跳次数
	WORD m_wTickDown0;  //下跳次数
	WORD m_wTickEqual0;
	float m_fTickUa0;   //上跳总额
	float m_fTickDa0;
	float m_fTickEa0;
	WORD m_wTick1;   //大单次数
	WORD m_wTickUp1;   //大单上跳次数
	WORD m_wTickDown1;  
	WORD m_wTickEqual1;
	float m_fTickA1;   //大单跳动总额
	float m_fTickUa1;   
	float m_fTickDa1;
	float m_fTickEa1;
	WORD m_wTick2;   //小单次数
	WORD m_wTickUp2;   
	WORD m_wTickDown2;  
	WORD m_wTickEqual2;
	float m_fTickA2;   
	float m_fTickUa2;   
	float m_fTickDa2;
	float m_fTickEa2;
	WORD m_wTick3;   //权重股次数
	WORD m_wTickUp3;   
	WORD m_wTickDown3;  
	WORD m_wTickEqual3;
	float m_fTickA3;   
	float m_fTickUa3;   
	float m_fTickDa3;
	float m_fTickEa3;
	WORD m_wTick4;   //巨单次数
	WORD m_wTickUp4;   
	WORD m_wTickDown4;  
	WORD m_wTickEqual4;
	float m_fTickA4;   
	float m_fTickUa4;   
	float m_fTickDa4;
	float m_fTickEa4;
	WORD m_wTick5;   //中单次数
	WORD m_wTickUp5;   
	WORD m_wTickDown5;  
	WORD m_wTickEqual5;
	float m_fTickA5;   
	float m_fTickUa5;   
	float m_fTickDa5;
	float m_fTickEa5;
	WORD m_wTick6;   //散单次数
	WORD m_wTickUp6;   
	WORD m_wTickDown6;  
	WORD m_wTickEqual6;
	float m_fTickA6;   
	float m_fTickUa6;   
	float m_fTickDa6;
	float m_fTickEa6;
	float m_fPrvTickPrice;
	float m_fPrvTickVomume;
	float m_fPrvTickAmount;
	float m_fPrvPrice;  //上一笔价格
	float m_fPrvVomume;  //上一笔量
	float m_fPrvAmount;  //上一笔额
	
	DWORD m_timeCalcZhangSu;   //上一个计算点
	DWORD m_timeCalcTick;      
	
	void * m_fOther;
	unsigned m_bReciveData : 1; //第一次接收新数据状态 0未接收 1已接收
	unsigned m_bVirtualData : 1; //当前数据是否是集合竞价的数据
	unsigned m_bIsBuy    : 1;         //是否为外盘
	unsigned m_bVirtualData2 : 1;
	unsigned m_bReloadPow : 1; //指示是否下次重新装载除权数据
	unsigned m_bIsMainInstrument : 1;//是否主力和约
	unsigned m_bBufopen : 1;   ////当前缓冲区是否被打开过
	unsigned m_nReserve5 : 1;
	unsigned m_nReserve6 : 1;
	void *  m_pMainStock;   //主力合约品种
	float m_fJieSuan;    //当前结算
	float m_fLastJieSuan;   //昨计算
	float m_upperLimitPrice;       // 涨停板
	float m_lowerLimitPrice;       // 跌停板
	
	float m_fBuyPrice6;        // 申买价6
	float m_fBuyVolume6;        // 申买量6
	float m_fSellPrice6;        // 申卖价6
	float m_fSellVolume6;        // 申卖量6
	
	float m_fBuyPrice7;        // 申买价7
	float m_fBuyVolume7;        // 申买量7
	float m_fSellPrice7;        // 申卖价7
	float m_fSellVolume7;        // 申卖量7
	
	float m_fBuyPrice8;        // 申买价8
	float m_fBuyVolume8;        // 申买量8
	float m_fSellPrice8;        // 申卖价8
	float m_fSellVolume8;        // 申卖量8
	
	float m_fBuyPrice9;        // 申买价9
	float m_fBuyVolume9;        // 申买量9
	float m_fSellPrice9;        // 申卖价9
	float m_fSellVolume9;        // 申卖量9
	
	float m_fBuyPrice10;        // 申买价10
	float m_fBuyVolume10;        // 申买量10
	float m_fSellPrice10;        // 申卖价10
	float m_fSellVolume10;       // 申卖量10
	
	long m_f1VirSub;         //主行情竞价分笔
	long m_f1size;         //主行情分笔数量,m_ptrSubBlcok=NULL表示只是记录不是真实缓冲区
	WORD m_f2size;         //竞价数量
	void * m_fOther2;      //文件数据块位置
	float m_fPrvVolume;
	void * m_fOther3;   //扩展统计自定义,为空表示取公共设置
}REPORT_STRUCT_EX;


//日线数据
typedef struct
{
	DATE	m_timeDate;				//UCT
	float	m_fOpen;			//开盘
	float	m_fHigh;			//最高
	float	m_fLow;				//最低
	float	m_fClose;			//收盘
	float	m_fOI;				//open interest
	float	m_fVolume;			//量
	float	m_fAmount;			//额
	WORD	m_wAdvance;			//涨数,仅大盘有效
	WORD	m_wDecline;			//跌数,仅大盘有效
	WORD	m_wQT;				//成交笔数
	float	m_fOpenVolume;		//开盘量
	float	m_fOpenAmount;		//开盘额	
}HISTORY_STRUCTEx;

//分笔成交数据结构
typedef struct{
	WORD m_fBuyVolume;
	WORD m_fSellVolume;	
	
	unsigned m_bOrder : 1;			//成交方向 1买盘 0卖盘
	unsigned m_timeV2 : 31;			// UCT
	
	float	m_fBuyPrice;								// 申买价1,2,3
	float	m_fSellPrice;							// 申卖价1,2,3
	
	float	m_fNewPrice;
	float	m_fOI;				//open interest
	float	m_fVolume;
	float	m_fAmount;
}SUBSECTION_REPORT;

//除权信息
typedef struct
{
	DATE	m_timeDate;			// UCT
	double	m_fGive;			// 每10股送
	double	m_fPei;				// 每10股配
	float   m_fGiveStock;		// 实际送股
	float   m_fPeiStock;		// 实际配股
	float	m_fPeiPrice;		// 配股价,仅当 m_fPei!=0.0f 时有效
	float	m_fProfit;			// 每10股红利
	float	m_fZhiJieStock;		// 直接上市(万股)
}POWER_STRUCTEx;

typedef struct  {
	WORD	m_nMarket;
	char	m_szLable[10];
}BLOCK_STRUCT;

////////////////////////////////////////////////////
//分析周期
////////////////////////////////////////////////////
enum CYC_DATA_TYPE
{
	MIN1_DATA=0,				//1分钟线
		MIN5_DATA,					//5分钟线					
		MIN15_DATA,					//15分钟线
		MIN30_DATA,					//30分钟线
		MIN60_DATA,					//60分钟线
		DAY_DATA,					//日线
		WEEK_DATA,					//周线
		MONTH_DATA,					//月线
		YEAR_DATA,					//年线
		MULTIDAY_DATA,				//多日线
		TICK_DATA,					//分笔成交
		MULTIHOUR_DATA,				//多小时线
		MULTISEC_DATA,				//多秒线
		MULTIMIN_DATA,				//多分钟线
		QUARTER_DATA,				//季度线
		SEMIYEAR_DATA,				//半年线
		SOLARTERM_DATA,				//节气线
		MIN3_DATA,					//3分钟线
		MIN10_DATA,					//10分钟线
		MULTITICK_DATA				//多笔
};

typedef struct  {
	float	m_all_capital_stock;	//总股本
	float	m_country_stock;		//A股本
	float	m_charter_member_corporation_stock;//发起人法人股
	float	m_corporation_stock;	//法人股
	float	m_stock_b;				//B股
	float	m_stock_h;				//H股
	float	m_stock_a;				//A股
	float	m_stock_employee;		//职工股
	float	m_stock_ration;		//A2转配股
	float	m_all_asset;			//总资产
	float	m_current_asset;		//流动资产
	float	m_fixed_asset;			//固定资产
	float	m_intangible_asset;		//无形资产
	float	m_long_invest;			//长期投资
	float	m_current_liabilities;	//流动负债
	float	m_long_term_liabilities;//长期负债
	float	m_capital_reserves;		//资本公积金
	float	m_every_capital_reserves;//每股公积金
	float	m_stockholder_equity;	//股东权益
	float	m_sales;				//主营收入
	float	m_gross_profit;			//主营利润
	float	m_other_operating_income;//其他利润
	float	m_operating_profit;		// 营业利润
	float	m_income_from_investments;//投资收益
	float	m_other_income;			//补贴收入
	float	m_extraordinary_income;// 营业外收支
	float	m_profit_and_loss;			//上年损益调整
	float	m_profit_before_taxes;	//利润总额
	float	m_profit_after_taxes;		//税后利润
	float	m_profit_aftert_only;		//净利润
	float	m_undistributed_profit;	//未分配利润
	float	m_undistributed_every_stock;//每股未分配
	float	m_stock_from_investments;	//每股收益
	float	m_assets_from_stock;		//每股净资产
	float	m_adjust_assets_from_stock;//调整每股净资
	float	m_stockholder_equity_rate;	//股东权益比
	float	m_purify_income;//净资收益率
	float	m_circulate_stock;//流通股
	float	m_fFin1;//经营现金流入
	float	m_fFin2;//经营现金流出
	float   m_fFin3;//经营现金流量
	float	m_fFin4;//投资现金流入
	float	m_fFin5;//投资现金流出
	float	m_fFin6;//投资现金流量
	float	m_fFin7;//筹资现金流入
	float	m_fFin8;//筹资现金流出
	float	m_fFin9;//筹资现金流量
	float	m_fFin10;//现金及等价物
	float	m_fFin11;//应收帐款周转率
	float	m_fFin12;//存货周转率
	float	m_fFin13;//股东总数
	float	m_fFin14;//发行价
	float	m_fFin15;//发行量
	float	m_fFin16;//主营业务增长率
	float	m_fFin17;//税后利润增长率
	float	m_fFin18;//净资增长率
	float	m_fFin19;//总资产增长率
	float	m_fFin20;
	float	m_fFin21;
	float	m_fFin22;
	float	m_fFin23;
	float	m_fFin24;
	float	m_fFin25;
	float	m_fFin26;
	float	m_fFin27;
	float	m_fFin28;
	DATE	m_timeUpdate;
}FINANCE_STRUCTEx;

typedef struct
{
	//////////////////////////////////////////////////////////////////////////
	//调用数据信息
	DWORD			m_dwVersion;			//调用软件版本(V2.10 : 0x210)
	DWORD			m_dwSerial;				//调用软件序列号
	char			m_szLabel[10];			//调用的品种代码
	WORD			m_wMarket;				//调用的品种市场，比如上海为'HS'
	CYC_DATA_TYPE	m_dataType;				//调用数据类型
	BYTE			m_bIsPow;				//是否复权
	BYTE			m_nPowType;				//复权类别 0向前复权 1向后复权
	BYTE			m_bIsReversePrice;		//是否反转价格
	DWORD			m_nDataCount;			//调用数据的数量，填0表示全部硬盘保存数据
	WORD			m_nCustomCyc;			//当周期类型为自定义周期时的自定义周期参数，为0则取系统默认设置
	BYTE			m_nReserve[3];
	
	//////////////////////////////////////////////////////////////////////////
	//以下为返回的数据信息	
	int					m_nNumData;			//数据数量
	HISTORY_STRUCTEx *  m_pMainData;		//主数据缓冲区
	
	SUBSECTION_REPORT * m_pSubsection;		//当日分笔成交明细
	int					m_nNumSubData;		//分笔数据量

	REPORT_STRUCT*		m_pReport;			//动态实时行情结构
	float*				m_pfFinData;		//财务数据(可以转换为 FINANCE_STRUCTEx 结构，如果不转换，请按FINANCE_STRUCTEx结构顺序使用
											//数组数据)
	
	POWER_STRUCTEx*	m_pSplitData;			//除权数据
	int				m_nNumSplitData;		//除权次数
}PCALCINFO;

typedef struct  {
	BLOCK_STRUCT m_stStock;   //单品种合约
	BYTE		 m_nBuySell;  //0 买入方向 1卖出方向
	WORD	     m_nVol;	  //下单数量
}TAOLI_INFO;

//////////////////////////////////////////////////////////////////////////
//消息包结构
//////////////////////////////////////////////////////////////////////////

typedef struct  {
	long m_nOrderID;
	char m_szAccount[31];
}CANCEL_ORDER_EX;

typedef struct  {
	long m_nOrderID;		//订单ID
	char m_szStatus[56];	//状态（详见.CPP文件描述）
	long m_nFilled;			//已成交数量(当m_szStatus="Tradeing"时，该参数为本次单笔成交数量)
	long m_nRemaining;		//剩余数量(当m_szStatus="Tradeing"时，该参数恒定为0)
	float m_fPrice;			//成交价格
	char m_szCode[10];		//品种
	char m_szMarket[3];		//市场
	BYTE m_nKaiping;		//开平仓 0开仓 1平仓
	BYTE m_nType;			//订单类型 0限价 1市价 2停损 3限价停损
	BYTE m_nAspect;			//买卖方向 0买入 1卖出
	char m_szAccount[32];	//操作账户
	BYTE m_nAccountType;	//账户类型 0IB 1CTP 2金仕达 3股票FIX 4恒生期货 5资管系统 6扩展接口
	float m_fAvgerPrice;    //持仓成本均价(仅当 m_nKaiping > 0 时有效)
}BARGAIN_NOTIFY_KSI;

#pragma pack (pop)

//主程序暴露给插件的接口
interface IMainFramework  
{
public:
	IMainFramework(){};
	virtual ~IMainFramework(){};
	
	//取得主窗口句柄
	virtual HWND   GetMainWindow() = 0;

	//取主程序版本号
	virtual DWORD GetVersion() = 0;

	//取指定品种数据,成功取得数据返回TRUE，否则为FALSE
	virtual BOOL  GetDataInfo(PCALCINFO * pInfo) = 0;

	//取指定品种的动态及时报表
	virtual REPORT_STRUCT * GetReportData(char * szLabel, WORD wMarket) = 0;

	//获取指定市场下的品种数量
	virtual DWORD  GetReportCount(WORD wMarket) = 0;

	//获取指定市场下基于0索引的品种代码
	//wMarket	输入参数, 指定市场
	//dwIndex	输入参数, 基于0索引的序号, 可以用GetReportCount函数获取
	//szCode	输出参数, 品种代码数组, 该数组空间不能小于10字节
	virtual BOOL   GetReportData(WORD wMarket, DWORD dwIndex, char * szCode) = 0;

	//取指定分类板块的品种数组
	//pBlock		存放品种的缓冲区地址
	//dwMaxCount	缓冲区存放品种数量大小
	//szName		为分类或者板块名称，如"上海A股"等
	//nMode			为类别，0市场分组，1分类板块，2系统板块（品种栏对应）
	//返回值：返回读取到的品种数量    
	virtual DWORD GetReportData(BLOCK_STRUCT * pBlock, DWORD dwMaxCount, char * szName, int nMode) = 0;

	//注册品种到数据通知，例如RegReportNotify("CL05",'MN');将合约注册到数据通知，当CL05有最新数据到达时触发ReportNotify事件。
	virtual BOOL RegReportNotify(char * szLabel, WORD wMarket) = 0;

	//取消品种数据注册，例如UnRegReportNotify("CL05",'MN')，CL05数据到达时不会再收到通知。
	virtual void UnRegReportNotify(char * szLabel, WORD wMarket) = 0;

	//下单委托交易
	// nType		下单类型 0限价 1市价 2停损 3限价停损
	// fLmtPrice	委托限价
	// fStopLmtPrice限价停损单（仅限IB外盘品种使用）
	// nVol		    委托数量
	// nAspect      0买入 1卖出
	// lpszLabel    品种名称
	// wMarket      品种市场
	// bMustOK      是否弹出下单确认
	// lpszAccount  下单帐户，为空则为当前活动帐户
	// nKaiPing     0开仓 1平仓 2平今
	// nTouBao      期货（0投机 1保值） 股票（0普通 1融资） 期权（0普通 1备兑）
	// bOrderQueue  是否为队列委托方式，即成交上一笔后再委托下一笔
	// 返回值 :     返回本次的委托编号
	// 注意：       请不要在SendMessage消息处理函数或者在线程中调用该下单函数。如果有必要在线程中调用下单，请使用PostMessage向主窗口发送下单
	//                 指令消息，然后在主线程中下单。
	virtual long PlaceOrder(BYTE nType, float fLmtPrice, float fStopLmtPrice, UINT nVol, BYTE nAspact, LPCSTR lpszLabel, WORD wMarket, 
		BOOL bMustOK, LPCSTR lpszAccount, BYTE nKaiPing, BYTE nTouBao, BYTE bOrderQueue) = 0;	

	//撤单
	// nOrderID     委托编号，即PlaceOrder委托下单的委托编号. 当bOrderQueue为2或3时,该变量为CANCEL_ORDER_EX结构体指针
	// bOrderQueue  是否为队列方式的委托撤单，即必须等到该笔撤单成功后再继续后续的下单任务
	//    当bOrderQueue=0时为 不使用队列下单 为1时为队列下单模式,当bOrderQueue为2或者3时为下列情况之一
	//    当为2时为CANCEL_ORDER_EX结构体中不用队列下单模式; 当为3时表示CANCEL_ORDER_EX结构体中,使用队列下单模式
	// 对于使用VC6等较低版本的编译器，LONG_PTR类型可能尚未指定而出现编译错误，将该类型定义为long即可。
	virtual void OrderCancel(LONG_PTR nOrderID, BYTE bOrderQueue) = 0;

	//注册WINDOWS窗口消息，金字塔将以事件方式通知各种
	virtual void RegisterMsg(HWND hMsgWnd, DWORD dwMsg) = 0;

	//得到套利合约信息
	//返回TRUE表示成功 ,返回套利指数内定义的套利品种信息
	virtual BOOL GetTaoliInfo(char * szTaoliLabel, TAOLI_INFO ** pTaoliInfo, DWORD * pdwCount) = 0;

	//得到IB外盘品种持仓数量
	virtual int GetHolding() = 0;

	//得到非IB外盘的指定账户的持仓数量
	virtual int GetHolding2(char * szAccount) = 0;

	//到所有IB帐户当前有效的未成交合约品种数量	
	virtual int GetOrderNum() = 0;

	//得到所有非IB外盘当前有效的未成交合约品种数量	
	virtual int GetOrderNum2() = 0;

	//得到IB帐户的成交明细数量	
	virtual int GetTradeCount() = 0;
	
	//得到指定帐户的非IB外盘帐户的成交明细数量	
	virtual int GetTradeCount2(char * szAccount) = 0;

	//当前已经登陆IB顾问帐户子帐户数量，若登陆的是IB普通帐户此属性为1	
	virtual int GetIBACCount() = 0;

	//当前已经登陆非IB外盘帐户数量（包含无效登陆等情况在内的）
	virtual int GetCTPAcCount() = 0;	

	/*得到当前默认帐户信息	
	nType        指定帐户信息类型。数值的内容含义请参考：http://www.weistock.com/WeisoftHelp/visualbasic_order_account.htm
	返回值：     返回VARIANT类型的账户结果，注意如果是BSTR类型的返回值请使用完毕后注意调用VariantClear函数释放内存。*/
	virtual VARIANT GetAccount(short nType) = 0;

	/*得到指定的非IB外盘帐户信息	
	nType        指定帐户信息类型。数值的内容含义请参考：http://www.weistock.com/WeisoftHelp/visualbasic_order_account2.htm
	szAccount    欲查询的账户
	返回值：     返回VARIANT类型的账户结果，注意如果是BSTR类型的返回值请使用完毕后注意调用VariantClear函数释放内存。*/
	virtual VARIANT GetAccount2(short nType, char * szAccount) = 0;

	/*取指定索引的持仓IB合约信息
	Index        输入参数，指定基于0索引的持仓和约信息，持仓和约总量参见 Holding 属性。
	Hold         输出参数，该该持仓品种持仓量，若空仓返回负数
	MktPrice     输出参数，该持仓品种市价
	AvgPrice     输出参数，该持仓品种均价
	MktValue     输出参数，该持仓品种市值
	AgeCost      输出参数，该持仓品种成本
	PNL          输出参数，该持仓品种浮动盈亏
	Code         输出参数，该持仓品种代码的返回数组,该数组空间至少需要10个字节
	Market       输出参数，该持仓品种市场
	返回值：      成功返回1，失败返回0 */
	virtual BOOL HoldingInfo(UINT Index, int &Hold, double &MktPrice, double &AvgPrice, double &MktValue, double &AgeCost, double &PNL, char *szCode,  WORD &Market)  = 0;	
	
	/*取指定索引的指定其他帐户(CTP,金仕达，恒生，股票等)的合约持仓信息	
	Index        输入参数，指定基于0索引的持仓和约信息，持仓和约总量参见 Holding2 属性。
	BuyHoding    输出参数，该该持仓品种买入持仓总量
	BuyCost      输出参数，该持仓品种持仓成本
	BuyTodayHoding     输出参数，该持仓品种今买持总量(对于证券市场，该参数为实际可用持仓)
	SellHoding     输出参数，该持仓品种卖出持仓总量
	SellCost      输出参数，该持仓品种卖出持仓成本
	SellTodayHoding 输出参数，该持仓品种的今卖出持仓总量(对于证券市场，该参数为实际可用持仓)
	PNL          输出参数，该持仓品种浮动盈亏
	UseMargin    输出参数，该持仓品种的保证金占用
	Code         输出参数，该持仓品种代码的返回数组,该数组空间至少需要10个字节
	Market       输出参数，该持仓品种市场
	Account      输入参数，可缺省，登陆其他帐户(CTP,金仕达，恒生，股票等)的帐户名称，若不填写则表示当前默认的帐户
	返回值：      成功返回1，失败返回0 */
	virtual BOOL HoldingInfo2(UINT Index, int &BuyHoding, double &BuyCost, int &BuyTodayHoding, int &SellHoding, double &SellCost, int &SellTodayHoding, double &PNL, double &UseMargin, char *szCode, WORD &Market, char * szAccount) = 0;

	/*
	*	取指定基于0索引的未成交IB合约信息
	Index        输入参数，指定基于0索引的持仓和约信息，持仓和约总量参见 OrderNum 属性。
	OrderID		 输出参数, 未成交订单ID
	ConSign      输出参数，本次委托数量
	Filled       输出参数，已成交数量
	Remaining    输出参数，未成交数量
	Action       输出参数，动作类型 0买入 1卖出
	OrderType    输出参数，订单类型 0限价 1市价 2停损 3市价停损
	LmtPrice     输出参数，当OrderType等于0时为限价，为3时为停损限价
	auxPrice     输出参数，停损价格
	Account      输出参数，帐户信息数组,该数组空间至少需要32个字节
	Code         输出参数，该持仓品种代码的返回数组,该数组空间至少需要10个字节
	Market       输出参数，该持仓品种市场
	返回值：      成功返回1，失败返回0
	*/
	virtual BOOL OrderInfo(UINT Index, int &OrderID, int &ConSign, int &Filled, int &Remaining, int &Action, int &OrderType, double &LmtPrice, double &auxPrice, char *szAccount, char *szCode, WORD &Market) = 0;
	
	/*取指定基于0索引的未成交其他帐户(CTP,金仕达，恒生，股票等)合约信息
	Index        输入参数，指定基于0索引的持仓和约信息，持仓和约总量参见 OrderNum2 属性。
	OrderID      输出参数, 未成交订单ID
	ConSign      输出参数，本次委托数量
	Filled       输出参数，已成交数量
	Remaining    输出参数，未成交数量
	Action       输出参数，动作类型 0买入 1卖出
	OrderType    输出参数，订单类型 0限价 1市价 2停损 3市价停损
	LmtPrice     输出参数，当OrderType等于0时为限价，为3时为停损限价
	Account      输出参数，帐户信息数组,该数组空间至少需要32个字节
	Kaiping      输出参数，开平仓类型 0开仓 1平仓
	Code         输出参数，该持仓品种代码的返回数组,该数组空间至少需要10个字节
	Market       输出参数，该持仓品种市场
	返回值：      成功返回1，失败返回0 */	
	virtual BOOL OrderInfo2(UINT Index, int &OrderID, int &ConSign, int &Filled, int &Remaining, int &Action, int &OrderType, double &LmtPrice, char *szAccount, int &Kaiping, char *szCode, WORD &Market) = 0;
	
	/*获取指定品种的合约种类
	Code         输入参数，指定的品种代码
	Market       输入参数，指定的品种市场
	返回值：是可以交易的非IB外盘接口品种返回1，IB接口返回0*/
	virtual int StockType(char * szCode, WORD wMarket)  = 0;

	/*取指定品种的和约信息
	Code         输入参数，指定的品种代码
	Market       输入参数，指定的品种市场
	Multipliter  输出参数，该品种的乘数/单位
	MinTick      输出参数，该品种的最小变动单位
	ShortPercent 输出参数，该品种的空头保证金
	LongPercent  输出参数，该品种的多头保证金 
	返回值：成功返回1否则返回0		
	*/
	virtual int GetContract(char *szCode, WORD wMarket, float &Multipliter, float &MinTick, float &ShortPercent, float &LongPercent) = 0;
	
	/*计算指定品种的本次交易手续费用。请用户在交易费率设置上预先设置好不同品种的各种交易费率情况，这样才能通过此方法得到正确的结果。
	Code         指定的品种代码
	Market       指定的品种市场
	lmtPrice     指定的限价
	Volume       委托数量
	Type         成交方向 0开仓 1平仓 2平今
	返回值：      返回计算后的手续费用*/
	virtual float GetChargeByNum(char * szCode, WORD wMarket, float lmtPrice, int Volume, int Type) = 0;
	
	/*取指定基于0索引序号的IB帐户成交明细
	Index        输入参数，基于0索引的成交明细
	Date         输出参数，成交时间
	Code         输出参数，该持仓品种代码的返回数组,该数组空间至少需要10个字节
	Market       输出参数，品种市场
	OrderType    输出参数，成交单类型，0限价 1市价 2停损 3限价停损
	Action       输出参数，成交方向 0买入 1卖出
	Price        输出参数，成交价格
	Volume       输出参数，成交量
	Account      输出参数，帐户信息数组,该数组空间至少需要32个字节
	返回值：      成功返回1，失败返回0*/
	virtual int TradeDetalied(int Index, DATE &Date, char *szCode, WORD &Market, int &OrderType, int &Action, float &Price, int &Volume, char *szAccount) = 0;
	
	/*取指定基于0索引序号的其他帐户(CTP,金仕达，恒生，股票等)帐户成交明细
	Index        输入参数，基于0索引的成交明细
	Date         输出参数，成交时间
	Code         输出参数，该持仓品种代码的返回数组,该数组空间至少需要10个字节
	Market       输出参数，品种市场
	OrderType    输出参数，成交单类型，0限价 1市价 2停损 3限价停损
	Action       输出参数，成交方向 0买入 1卖出
	Price        输出参数，成交价格
	Volume       输出参数，成交量
	Kaiping      输出参数，开平仓类型，0开仓 1平仓
	Account      输入参数，成交帐户，可省略，若省略则表示当前默认激活帐户
	返回值：      成功返回1，失败返回0*/
	virtual int TradeDetalied2(int Index, DATE &Date, char *szCode, WORD &Market, int &OrderType, int &Action, float &Price, int &Volume, int &Kaiping, char *szAccount) = 0;
	
	//得到指定基于0索引的IB帐户名称，例如IBAccountName（0）表示取第一个登陆的IB帐户	
	//nIndex	输入参数，基于0索引的IB登录账户索引
	//szAccont  输出参数,帐户信息数组,该数组空间至少需要32个字节
	//返回值    成功返回true,否则返回 false
	virtual bool GetIBAccountName(int nIndex, char * szAccount) = 0;
	
	//得到指定基于0索引的其他帐户(CTP,金仕达，恒生，股票等)帐户名称（包含登陆未成功的），例如 CTPAccountName（0）表示取第一个登陆的用户名称	
	//nIndex	输入参数，基于0索引的IB登录账户索引
	//szAccont  输出参数,帐户信息数组,该数组空间至少需要32个字节
	//返回值    成功返回true,否则返回 false
	virtual bool GetCTPAccountName(int nIndex, char * szAccount) = 0;
	
	//判断指定帐号是否是当前已登录有效帐号，例如 Order.IsAccount("351579")，如果该账户已登录则返回1，否则返回0	
	virtual int IsAccount(char *szAccount) = 0;

	//获取指定品种的动态行情
	//	Code         指定的品种代码
	//	Market       指定的品种市场
	//  nType		 动态品种的行情类型，具体使用请参考PEL语言的DYNAINFO函数的类型参数
	//               参考 http://www.weistock.com/WeisoftHelp/fulua_dynainfo.htm
	//  返回值		 返回计算出的指定值，若调用失败，则返回无效值
	virtual float GetDynainfo(char * szCode, WORD wMarket, int nType) = 0;

	//扩展数据接口，利用这个接口实现未来的接口功能扩充
	virtual void * ExpandFunction(void * pSt, int nType) = 0;
	

	//////////////////////////////////////////////////////////////////////////
	//						期权方面的信息
	//////////////////////////////////////////////////////////////////////////

	//获取期权品种的特征值
	//	Code         指定的品种代码
	//	Market       指定的品种市场
	//  nType		 动态品种的行情类型，具体使用请参考 http://www.weistock.com/WeisoftHelp/fulua_optioninfo.htm
	//  返回值		 返回计算出的指定值
	virtual VARIANT OptionInfo(char * szCode, WORD wMarket, int nType) = 0;
};

#endif