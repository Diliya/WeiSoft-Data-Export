/*
///////////////////////////////////////////////////////////////////////////
��������C++���Խӿڡ����ýӿڹ淶V3.0
����Ŀʹ��MFC����DLL�����ģ��������չ���޸�Ϊadi�ļ������ڽ�������Ŀ¼��
�������������ڹ��߲˵�->��չ�����˵���,���Կ�����Ĳ��.

ע�⣺
1�����ڱ���RELEASE�汾���в������Ҫ��DEBUG��
2����ע��������İ汾,�����x64ģʽ�Ľ������汾,�뽫���DLLҲ�����64λ�汾�ſ���ʹ�á�

  'QS'�Ϻ��ڻ��г�,�г������ʾ��һ��WROD���͵�,�ַ���ʾ�� "SH", ����WORD ��Ϊ 'HS'
  ����ÿ���г��Ĵ����ڹ��߲˵�->�г�������,�鿴�г��Ĵ���,���úͽ��й���.
*/


#if !defined(__ADDININTERFACE_EX_H__)
#define __ADDININTERFACE_EX_H__

#define		STKLABEL_LEN			10			// �ɺ����ݳ���,�����г��ɺű������Ǯ��
#define		STKNAME_LEN				32			// ��������

#pragma pack (push ,1)

//��̬�������ݽṹ
typedef struct	
{
	DWORD	m_time;										// �ɽ�ʱ��(time_t)
	
	float	m_fLastClose;								// ����
	float	m_fOpen;									// ��
	float	m_fHigh;									// ���
	float	m_fLow;										// ���
	float	m_fNewPrice;								// ����
	float	m_fOI;										//open interest
	float	m_fLastOI;
	float	m_fVolume;									// �ɽ���
	float	m_fAmount;									// �ɽ���
	
	float	m_fLastOpen;								//ǰ��
	float	m_fLastHigh;								//ǰ��
	float	m_fLastLow;									//ǰ��
	
	float	m_fBuyPrice[3];								// �����1,2,3
	float	m_fBuyVolume[3];							// ������1,2,3
	float	m_fSellPrice[3];							// ������1,2,3
	float	m_fSellVolume[3];							// ������1,2,3
	
	float	m_fBuyPrice4;								// �����4
	float	m_fBuyVolume4;								// ������4
	float	m_fSellPrice4;								// ������4
	float	m_fSellVolume4;								// ������4
	
	float	m_fBuyPrice5;								// �����5
	float	m_fBuyVolume5;								// ������5
	float	m_fSellPrice5;								// ������5
	float	m_fSellVolume5;								// ������5
	
	float	m_fVolumeNow;								//����
	float	m_fBuyVol;									//������
	float	m_fSellVol;									//������
	char	m_szName[32];								// ��Ʊ����,��'\0'��β
	char	m_szNamePY[16];
	char	m_szLabel[10];								// ��Ʊ����,��'\0'��β
	float   m_f5DayAverage;								//5�վ���
	float	m_fNext5DayVol;								//��һ��5�վ���
	DWORD	m_timeHardenSpeed;							//����ǰ�Ƚ�ʱ��
	float	m_fHardenSpeed;								//�����ñ�������¼ǰ5���Ӽ۸�
	WORD	m_wMarket;									//Ʒ�������г������Ϻ�'HS',����'ZS'
}REPORT_STRUCT;

//��չ��̬�������ݽṹ
typedef struct 
{
	DWORD m_time;          // �ɽ�ʱ��
	
	float m_fLastClose;        // ����
	float m_fOpen;         // ��
	float m_fHigh;         // ���
	float m_fLow;          // ���
	float m_fNewPrice;        // ����
	float m_fOI;    //open interest
	float m_fLastOI;
	float m_fVolume;         // �ɽ���
	float m_fAmount;         // �ɽ���
	
	float m_fLastOpen;  //ǰ��
	float m_fLastHigh;  //ǰ��
	float m_fLastLow;   //ǰ��
	
	float m_fBuyPrice[3];        // �����1,2,3
	float m_fBuyVolume[3];       // ������1,2,3
	float m_fSellPrice[3];       // ������1,2,3
	float m_fSellVolume[3];       // ������1,2,3
	
	float m_fBuyPrice4;        // �����4
	float m_fBuyVolume4;        // ������4
	float m_fSellPrice4;        // ������4
	float m_fSellVolume4;        // ������4
	
	float m_fBuyPrice5;        // �����5
	float m_fBuyVolume5;        // ������5
	float m_fSellPrice5;        // ������5
	float m_fSellVolume5;        // ������5
	
	float m_fVolumeNow;        //����
	float m_fBuyVol;         //������
	float m_fSellVol;         //������
	char m_szName[32];      // ��Ʊ����,��'\0'��β
	char m_szNamePY[16];
	char m_szLabel[10];     // ��Ʊ����,��'\0'��β
	float   m_f5DayAverage;        //5�վ���
	float m_fNext5DayVol;        //��һ��5�վ���
	DWORD m_timeHardenSpeed;       //����ǰ�Ƚ�ʱ��
	float m_fHardenSpeed;        //�����ñ�������¼ǰ5���Ӽ۸�
	WORD m_wMarket;
	
	float m_fBuyAmount;        //���̶�
	float m_fSellAmount;        //���̶�
	float m_fPoweru;         //��������
	float   m_fPowerd;
	WORD    m_nBuyBi;         //�������
	WORD    m_nSellBi;
	float m_fAmountNow;        //�ֶ�
	WORD m_wBorNum;         //�ɽ���������
	WORD    m_wSorNum;
	BYTE m_nOrnumType;        //�ɽ��������� 1���� 0����
	WORD m_wTickUp0;   //��������
	WORD m_wTickDown0;  //��������
	WORD m_wTickEqual0;
	float m_fTickUa0;   //�����ܶ�
	float m_fTickDa0;
	float m_fTickEa0;
	WORD m_wTick1;   //�󵥴���
	WORD m_wTickUp1;   //����������
	WORD m_wTickDown1;  
	WORD m_wTickEqual1;
	float m_fTickA1;   //�������ܶ�
	float m_fTickUa1;   
	float m_fTickDa1;
	float m_fTickEa1;
	WORD m_wTick2;   //С������
	WORD m_wTickUp2;   
	WORD m_wTickDown2;  
	WORD m_wTickEqual2;
	float m_fTickA2;   
	float m_fTickUa2;   
	float m_fTickDa2;
	float m_fTickEa2;
	WORD m_wTick3;   //Ȩ�عɴ���
	WORD m_wTickUp3;   
	WORD m_wTickDown3;  
	WORD m_wTickEqual3;
	float m_fTickA3;   
	float m_fTickUa3;   
	float m_fTickDa3;
	float m_fTickEa3;
	WORD m_wTick4;   //�޵�����
	WORD m_wTickUp4;   
	WORD m_wTickDown4;  
	WORD m_wTickEqual4;
	float m_fTickA4;   
	float m_fTickUa4;   
	float m_fTickDa4;
	float m_fTickEa4;
	WORD m_wTick5;   //�е�����
	WORD m_wTickUp5;   
	WORD m_wTickDown5;  
	WORD m_wTickEqual5;
	float m_fTickA5;   
	float m_fTickUa5;   
	float m_fTickDa5;
	float m_fTickEa5;
	WORD m_wTick6;   //ɢ������
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
	float m_fPrvPrice;  //��һ�ʼ۸�
	float m_fPrvVomume;  //��һ����
	float m_fPrvAmount;  //��һ�ʶ�
	
	DWORD m_timeCalcZhangSu;   //��һ�������
	DWORD m_timeCalcTick;      
	
	void * m_fOther;
	unsigned m_bReciveData : 1; //��һ�ν���������״̬ 0δ���� 1�ѽ���
	unsigned m_bVirtualData : 1; //��ǰ�����Ƿ��Ǽ��Ͼ��۵�����
	unsigned m_bIsBuy    : 1;         //�Ƿ�Ϊ����
	unsigned m_bVirtualData2 : 1;
	unsigned m_bReloadPow : 1; //ָʾ�Ƿ��´�����װ�س�Ȩ����
	unsigned m_bIsMainInstrument : 1;//�Ƿ�������Լ
	unsigned m_bBufopen : 1;   ////��ǰ�������Ƿ񱻴򿪹�
	unsigned m_nReserve5 : 1;
	unsigned m_nReserve6 : 1;
	void *  m_pMainStock;   //������ԼƷ��
	float m_fJieSuan;    //��ǰ����
	float m_fLastJieSuan;   //�����
	float m_upperLimitPrice;       // ��ͣ��
	float m_lowerLimitPrice;       // ��ͣ��
	
	float m_fBuyPrice6;        // �����6
	float m_fBuyVolume6;        // ������6
	float m_fSellPrice6;        // ������6
	float m_fSellVolume6;        // ������6
	
	float m_fBuyPrice7;        // �����7
	float m_fBuyVolume7;        // ������7
	float m_fSellPrice7;        // ������7
	float m_fSellVolume7;        // ������7
	
	float m_fBuyPrice8;        // �����8
	float m_fBuyVolume8;        // ������8
	float m_fSellPrice8;        // ������8
	float m_fSellVolume8;        // ������8
	
	float m_fBuyPrice9;        // �����9
	float m_fBuyVolume9;        // ������9
	float m_fSellPrice9;        // ������9
	float m_fSellVolume9;        // ������9
	
	float m_fBuyPrice10;        // �����10
	float m_fBuyVolume10;        // ������10
	float m_fSellPrice10;        // ������10
	float m_fSellVolume10;       // ������10
	
	long m_f1VirSub;         //�����龺�۷ֱ�
	long m_f1size;         //������ֱ�����,m_ptrSubBlcok=NULL��ʾֻ�Ǽ�¼������ʵ������
	WORD m_f2size;         //��������
	void * m_fOther2;      //�ļ����ݿ�λ��
	float m_fPrvVolume;
	void * m_fOther3;   //��չͳ���Զ���,Ϊ�ձ�ʾȡ��������
}REPORT_STRUCT_EX;


//��������
typedef struct
{
	DATE	m_timeDate;				//UCT
	float	m_fOpen;			//����
	float	m_fHigh;			//���
	float	m_fLow;				//���
	float	m_fClose;			//����
	float	m_fOI;				//open interest
	float	m_fVolume;			//��
	float	m_fAmount;			//��
	WORD	m_wAdvance;			//����,��������Ч
	WORD	m_wDecline;			//����,��������Ч
	WORD	m_wQT;				//�ɽ�����
	float	m_fOpenVolume;		//������
	float	m_fOpenAmount;		//���̶�	
}HISTORY_STRUCTEx;

//�ֱʳɽ����ݽṹ
typedef struct{
	WORD m_fBuyVolume;
	WORD m_fSellVolume;	
	
	unsigned m_bOrder : 1;			//�ɽ����� 1���� 0����
	unsigned m_timeV2 : 31;			// UCT
	
	float	m_fBuyPrice;								// �����1,2,3
	float	m_fSellPrice;							// ������1,2,3
	
	float	m_fNewPrice;
	float	m_fOI;				//open interest
	float	m_fVolume;
	float	m_fAmount;
}SUBSECTION_REPORT;

//��Ȩ��Ϣ
typedef struct
{
	DATE	m_timeDate;			// UCT
	double	m_fGive;			// ÿ10����
	double	m_fPei;				// ÿ10����
	float   m_fGiveStock;		// ʵ���͹�
	float   m_fPeiStock;		// ʵ�����
	float	m_fPeiPrice;		// ��ɼ�,���� m_fPei!=0.0f ʱ��Ч
	float	m_fProfit;			// ÿ10�ɺ���
	float	m_fZhiJieStock;		// ֱ������(���)
}POWER_STRUCTEx;

typedef struct  {
	WORD	m_nMarket;
	char	m_szLable[10];
}BLOCK_STRUCT;

////////////////////////////////////////////////////
//��������
////////////////////////////////////////////////////
enum CYC_DATA_TYPE
{
	MIN1_DATA=0,				//1������
		MIN5_DATA,					//5������					
		MIN15_DATA,					//15������
		MIN30_DATA,					//30������
		MIN60_DATA,					//60������
		DAY_DATA,					//����
		WEEK_DATA,					//����
		MONTH_DATA,					//����
		YEAR_DATA,					//����
		MULTIDAY_DATA,				//������
		TICK_DATA,					//�ֱʳɽ�
		MULTIHOUR_DATA,				//��Сʱ��
		MULTISEC_DATA,				//������
		MULTIMIN_DATA,				//�������
		QUARTER_DATA,				//������
		SEMIYEAR_DATA,				//������
		SOLARTERM_DATA,				//������
		MIN3_DATA,					//3������
		MIN10_DATA,					//10������
		MULTITICK_DATA				//���
};

typedef struct  {
	float	m_all_capital_stock;	//�ܹɱ�
	float	m_country_stock;		//A�ɱ�
	float	m_charter_member_corporation_stock;//�����˷��˹�
	float	m_corporation_stock;	//���˹�
	float	m_stock_b;				//B��
	float	m_stock_h;				//H��
	float	m_stock_a;				//A��
	float	m_stock_employee;		//ְ����
	float	m_stock_ration;		//A2ת���
	float	m_all_asset;			//���ʲ�
	float	m_current_asset;		//�����ʲ�
	float	m_fixed_asset;			//�̶��ʲ�
	float	m_intangible_asset;		//�����ʲ�
	float	m_long_invest;			//����Ͷ��
	float	m_current_liabilities;	//������ծ
	float	m_long_term_liabilities;//���ڸ�ծ
	float	m_capital_reserves;		//�ʱ�������
	float	m_every_capital_reserves;//ÿ�ɹ�����
	float	m_stockholder_equity;	//�ɶ�Ȩ��
	float	m_sales;				//��Ӫ����
	float	m_gross_profit;			//��Ӫ����
	float	m_other_operating_income;//��������
	float	m_operating_profit;		// Ӫҵ����
	float	m_income_from_investments;//Ͷ������
	float	m_other_income;			//��������
	float	m_extraordinary_income;// Ӫҵ����֧
	float	m_profit_and_loss;			//�����������
	float	m_profit_before_taxes;	//�����ܶ�
	float	m_profit_after_taxes;		//˰������
	float	m_profit_aftert_only;		//������
	float	m_undistributed_profit;	//δ��������
	float	m_undistributed_every_stock;//ÿ��δ����
	float	m_stock_from_investments;	//ÿ������
	float	m_assets_from_stock;		//ÿ�ɾ��ʲ�
	float	m_adjust_assets_from_stock;//����ÿ�ɾ���
	float	m_stockholder_equity_rate;	//�ɶ�Ȩ���
	float	m_purify_income;//����������
	float	m_circulate_stock;//��ͨ��
	float	m_fFin1;//��Ӫ�ֽ�����
	float	m_fFin2;//��Ӫ�ֽ�����
	float   m_fFin3;//��Ӫ�ֽ�����
	float	m_fFin4;//Ͷ���ֽ�����
	float	m_fFin5;//Ͷ���ֽ�����
	float	m_fFin6;//Ͷ���ֽ�����
	float	m_fFin7;//�����ֽ�����
	float	m_fFin8;//�����ֽ�����
	float	m_fFin9;//�����ֽ�����
	float	m_fFin10;//�ֽ𼰵ȼ���
	float	m_fFin11;//Ӧ���ʿ���ת��
	float	m_fFin12;//�����ת��
	float	m_fFin13;//�ɶ�����
	float	m_fFin14;//���м�
	float	m_fFin15;//������
	float	m_fFin16;//��Ӫҵ��������
	float	m_fFin17;//˰������������
	float	m_fFin18;//����������
	float	m_fFin19;//���ʲ�������
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
	//����������Ϣ
	DWORD			m_dwVersion;			//��������汾(V2.10 : 0x210)
	DWORD			m_dwSerial;				//����������к�
	char			m_szLabel[10];			//���õ�Ʒ�ִ���
	WORD			m_wMarket;				//���õ�Ʒ���г��������Ϻ�Ϊ'HS'
	CYC_DATA_TYPE	m_dataType;				//������������
	BYTE			m_bIsPow;				//�Ƿ�Ȩ
	BYTE			m_nPowType;				//��Ȩ��� 0��ǰ��Ȩ 1���Ȩ
	BYTE			m_bIsReversePrice;		//�Ƿ�ת�۸�
	DWORD			m_nDataCount;			//�������ݵ���������0��ʾȫ��Ӳ�̱�������
	WORD			m_nCustomCyc;			//����������Ϊ�Զ�������ʱ���Զ������ڲ�����Ϊ0��ȡϵͳĬ������
	BYTE			m_nReserve[3];
	
	//////////////////////////////////////////////////////////////////////////
	//����Ϊ���ص�������Ϣ	
	int					m_nNumData;			//��������
	HISTORY_STRUCTEx *  m_pMainData;		//�����ݻ�����
	
	SUBSECTION_REPORT * m_pSubsection;		//���շֱʳɽ���ϸ
	int					m_nNumSubData;		//�ֱ�������

	REPORT_STRUCT*		m_pReport;			//��̬ʵʱ����ṹ
	float*				m_pfFinData;		//��������(����ת��Ϊ FINANCE_STRUCTEx �ṹ�������ת�����밴FINANCE_STRUCTEx�ṹ˳��ʹ��
											//��������)
	
	POWER_STRUCTEx*	m_pSplitData;			//��Ȩ����
	int				m_nNumSplitData;		//��Ȩ����
}PCALCINFO;

typedef struct  {
	BLOCK_STRUCT m_stStock;   //��Ʒ�ֺ�Լ
	BYTE		 m_nBuySell;  //0 ���뷽�� 1��������
	WORD	     m_nVol;	  //�µ�����
}TAOLI_INFO;

//////////////////////////////////////////////////////////////////////////
//��Ϣ���ṹ
//////////////////////////////////////////////////////////////////////////

typedef struct  {
	long m_nOrderID;
	char m_szAccount[31];
}CANCEL_ORDER_EX;

typedef struct  {
	long m_nOrderID;		//����ID
	char m_szStatus[56];	//״̬�����.CPP�ļ�������
	long m_nFilled;			//�ѳɽ�����(��m_szStatus="Tradeing"ʱ���ò���Ϊ���ε��ʳɽ�����)
	long m_nRemaining;		//ʣ������(��m_szStatus="Tradeing"ʱ���ò����㶨Ϊ0)
	float m_fPrice;			//�ɽ��۸�
	char m_szCode[10];		//Ʒ��
	char m_szMarket[3];		//�г�
	BYTE m_nKaiping;		//��ƽ�� 0���� 1ƽ��
	BYTE m_nType;			//�������� 0�޼� 1�м� 2ͣ�� 3�޼�ͣ��
	BYTE m_nAspect;			//�������� 0���� 1����
	char m_szAccount[32];	//�����˻�
	BYTE m_nAccountType;	//�˻����� 0IB 1CTP 2���˴� 3��ƱFIX 4�����ڻ� 5�ʹ�ϵͳ 6��չ�ӿ�
	float m_fAvgerPrice;    //�ֲֳɱ�����(���� m_nKaiping > 0 ʱ��Ч)
}BARGAIN_NOTIFY_KSI;

#pragma pack (pop)

//������¶������Ľӿ�
interface IMainFramework  
{
public:
	IMainFramework(){};
	virtual ~IMainFramework(){};
	
	//ȡ�������ھ��
	virtual HWND   GetMainWindow() = 0;

	//ȡ������汾��
	virtual DWORD GetVersion() = 0;

	//ȡָ��Ʒ������,�ɹ�ȡ�����ݷ���TRUE������ΪFALSE
	virtual BOOL  GetDataInfo(PCALCINFO * pInfo) = 0;

	//ȡָ��Ʒ�ֵĶ�̬��ʱ����
	virtual REPORT_STRUCT * GetReportData(char * szLabel, WORD wMarket) = 0;

	//��ȡָ���г��µ�Ʒ������
	virtual DWORD  GetReportCount(WORD wMarket) = 0;

	//��ȡָ���г��»���0������Ʒ�ִ���
	//wMarket	�������, ָ���г�
	//dwIndex	�������, ����0���������, ������GetReportCount������ȡ
	//szCode	�������, Ʒ�ִ�������, ������ռ䲻��С��10�ֽ�
	virtual BOOL   GetReportData(WORD wMarket, DWORD dwIndex, char * szCode) = 0;

	//ȡָ���������Ʒ������
	//pBlock		���Ʒ�ֵĻ�������ַ
	//dwMaxCount	���������Ʒ��������С
	//szName		Ϊ������߰�����ƣ���"�Ϻ�A��"��
	//nMode			Ϊ���0�г����飬1�����飬2ϵͳ��飨Ʒ������Ӧ��
	//����ֵ�����ض�ȡ����Ʒ������    
	virtual DWORD GetReportData(BLOCK_STRUCT * pBlock, DWORD dwMaxCount, char * szName, int nMode) = 0;

	//ע��Ʒ�ֵ�����֪ͨ������RegReportNotify("CL05",'MN');����Լע�ᵽ����֪ͨ����CL05���������ݵ���ʱ����ReportNotify�¼���
	virtual BOOL RegReportNotify(char * szLabel, WORD wMarket) = 0;

	//ȡ��Ʒ������ע�ᣬ����UnRegReportNotify("CL05",'MN')��CL05���ݵ���ʱ�������յ�֪ͨ��
	virtual void UnRegReportNotify(char * szLabel, WORD wMarket) = 0;

	//�µ�ί�н���
	// nType		�µ����� 0�޼� 1�м� 2ͣ�� 3�޼�ͣ��
	// fLmtPrice	ί���޼�
	// fStopLmtPrice�޼�ͣ�𵥣�����IB����Ʒ��ʹ�ã�
	// nVol		    ί������
	// nAspect      0���� 1����
	// lpszLabel    Ʒ������
	// wMarket      Ʒ���г�
	// bMustOK      �Ƿ񵯳��µ�ȷ��
	// lpszAccount  �µ��ʻ���Ϊ����Ϊ��ǰ��ʻ�
	// nKaiPing     0���� 1ƽ�� 2ƽ��
	// nTouBao      �ڻ���0Ͷ�� 1��ֵ�� ��Ʊ��0��ͨ 1���ʣ� ��Ȩ��0��ͨ 1���ң�
	// bOrderQueue  �Ƿ�Ϊ����ί�з�ʽ�����ɽ���һ�ʺ���ί����һ��
	// ����ֵ :     ���ر��ε�ί�б��
	// ע�⣺       �벻Ҫ��SendMessage��Ϣ�������������߳��е��ø��µ�����������б�Ҫ���߳��е����µ�����ʹ��PostMessage�������ڷ����µ�
	//                 ָ����Ϣ��Ȼ�������߳����µ���
	virtual long PlaceOrder(BYTE nType, float fLmtPrice, float fStopLmtPrice, UINT nVol, BYTE nAspact, LPCSTR lpszLabel, WORD wMarket, 
		BOOL bMustOK, LPCSTR lpszAccount, BYTE nKaiPing, BYTE nTouBao, BYTE bOrderQueue) = 0;	

	//����
	// nOrderID     ί�б�ţ���PlaceOrderί���µ���ί�б��. ��bOrderQueueΪ2��3ʱ,�ñ���ΪCANCEL_ORDER_EX�ṹ��ָ��
	// bOrderQueue  �Ƿ�Ϊ���з�ʽ��ί�г�����������ȵ��ñʳ����ɹ����ټ����������µ�����
	//    ��bOrderQueue=0ʱΪ ��ʹ�ö����µ� Ϊ1ʱΪ�����µ�ģʽ,��bOrderQueueΪ2����3ʱΪ�������֮һ
	//    ��Ϊ2ʱΪCANCEL_ORDER_EX�ṹ���в��ö����µ�ģʽ; ��Ϊ3ʱ��ʾCANCEL_ORDER_EX�ṹ����,ʹ�ö����µ�ģʽ
	// ����ʹ��VC6�ȽϵͰ汾�ı�������LONG_PTR���Ϳ�����δָ�������ֱ�����󣬽������Ͷ���Ϊlong���ɡ�
	virtual void OrderCancel(LONG_PTR nOrderID, BYTE bOrderQueue) = 0;

	//ע��WINDOWS������Ϣ�������������¼���ʽ֪ͨ����
	virtual void RegisterMsg(HWND hMsgWnd, DWORD dwMsg) = 0;

	//�õ�������Լ��Ϣ
	//����TRUE��ʾ�ɹ� ,��������ָ���ڶ��������Ʒ����Ϣ
	virtual BOOL GetTaoliInfo(char * szTaoliLabel, TAOLI_INFO ** pTaoliInfo, DWORD * pdwCount) = 0;

	//�õ�IB����Ʒ�ֲֳ�����
	virtual int GetHolding() = 0;

	//�õ���IB���̵�ָ���˻��ĳֲ�����
	virtual int GetHolding2(char * szAccount) = 0;

	//������IB�ʻ���ǰ��Ч��δ�ɽ���ԼƷ������	
	virtual int GetOrderNum() = 0;

	//�õ����з�IB���̵�ǰ��Ч��δ�ɽ���ԼƷ������	
	virtual int GetOrderNum2() = 0;

	//�õ�IB�ʻ��ĳɽ���ϸ����	
	virtual int GetTradeCount() = 0;
	
	//�õ�ָ���ʻ��ķ�IB�����ʻ��ĳɽ���ϸ����	
	virtual int GetTradeCount2(char * szAccount) = 0;

	//��ǰ�Ѿ���½IB�����ʻ����ʻ�����������½����IB��ͨ�ʻ�������Ϊ1	
	virtual int GetIBACCount() = 0;

	//��ǰ�Ѿ���½��IB�����ʻ�������������Ч��½��������ڵģ�
	virtual int GetCTPAcCount() = 0;	

	/*�õ���ǰĬ���ʻ���Ϣ	
	nType        ָ���ʻ���Ϣ���͡���ֵ�����ݺ�����ο���http://www.weistock.com/WeisoftHelp/visualbasic_order_account.htm
	����ֵ��     ����VARIANT���͵��˻������ע�������BSTR���͵ķ���ֵ��ʹ����Ϻ�ע�����VariantClear�����ͷ��ڴ档*/
	virtual VARIANT GetAccount(short nType) = 0;

	/*�õ�ָ���ķ�IB�����ʻ���Ϣ	
	nType        ָ���ʻ���Ϣ���͡���ֵ�����ݺ�����ο���http://www.weistock.com/WeisoftHelp/visualbasic_order_account2.htm
	szAccount    ����ѯ���˻�
	����ֵ��     ����VARIANT���͵��˻������ע�������BSTR���͵ķ���ֵ��ʹ����Ϻ�ע�����VariantClear�����ͷ��ڴ档*/
	virtual VARIANT GetAccount2(short nType, char * szAccount) = 0;

	/*ȡָ�������ĳֲ�IB��Լ��Ϣ
	Index        ���������ָ������0�����ĳֲֺ�Լ��Ϣ���ֲֺ�Լ�����μ� Holding ���ԡ�
	Hold         ����������øóֲ�Ʒ�ֲֳ��������ղַ��ظ���
	MktPrice     ����������óֲ�Ʒ���м�
	AvgPrice     ����������óֲ�Ʒ�־���
	MktValue     ����������óֲ�Ʒ����ֵ
	AgeCost      ����������óֲ�Ʒ�ֳɱ�
	PNL          ����������óֲ�Ʒ�ָ���ӯ��
	Code         ����������óֲ�Ʒ�ִ���ķ�������,������ռ�������Ҫ10���ֽ�
	Market       ����������óֲ�Ʒ���г�
	����ֵ��      �ɹ�����1��ʧ�ܷ���0 */
	virtual BOOL HoldingInfo(UINT Index, int &Hold, double &MktPrice, double &AvgPrice, double &MktValue, double &AgeCost, double &PNL, char *szCode,  WORD &Market)  = 0;	
	
	/*ȡָ��������ָ�������ʻ�(CTP,���˴��������Ʊ��)�ĺ�Լ�ֲ���Ϣ	
	Index        ���������ָ������0�����ĳֲֺ�Լ��Ϣ���ֲֺ�Լ�����μ� Holding2 ���ԡ�
	BuyHoding    ����������øóֲ�Ʒ������ֲ�����
	BuyCost      ����������óֲ�Ʒ�ֲֳֳɱ�
	BuyTodayHoding     ����������óֲ�Ʒ�ֽ��������(����֤ȯ�г����ò���Ϊʵ�ʿ��óֲ�)
	SellHoding     ����������óֲ�Ʒ�������ֲ�����
	SellCost      ����������óֲ�Ʒ�������ֲֳɱ�
	SellTodayHoding ����������óֲ�Ʒ�ֵĽ������ֲ�����(����֤ȯ�г����ò���Ϊʵ�ʿ��óֲ�)
	PNL          ����������óֲ�Ʒ�ָ���ӯ��
	UseMargin    ����������óֲ�Ʒ�ֵı�֤��ռ��
	Code         ����������óֲ�Ʒ�ִ���ķ�������,������ռ�������Ҫ10���ֽ�
	Market       ����������óֲ�Ʒ���г�
	Account      �����������ȱʡ����½�����ʻ�(CTP,���˴��������Ʊ��)���ʻ����ƣ�������д���ʾ��ǰĬ�ϵ��ʻ�
	����ֵ��      �ɹ�����1��ʧ�ܷ���0 */
	virtual BOOL HoldingInfo2(UINT Index, int &BuyHoding, double &BuyCost, int &BuyTodayHoding, int &SellHoding, double &SellCost, int &SellTodayHoding, double &PNL, double &UseMargin, char *szCode, WORD &Market, char * szAccount) = 0;

	/*
	*	ȡָ������0������δ�ɽ�IB��Լ��Ϣ
	Index        ���������ָ������0�����ĳֲֺ�Լ��Ϣ���ֲֺ�Լ�����μ� OrderNum ���ԡ�
	OrderID		 �������, δ�ɽ�����ID
	ConSign      �������������ί������
	Filled       ����������ѳɽ�����
	Remaining    ���������δ�ɽ�����
	Action       ����������������� 0���� 1����
	OrderType    ����������������� 0�޼� 1�м� 2ͣ�� 3�м�ͣ��
	LmtPrice     �����������OrderType����0ʱΪ�޼ۣ�Ϊ3ʱΪͣ���޼�
	auxPrice     ���������ͣ��۸�
	Account      ����������ʻ���Ϣ����,������ռ�������Ҫ32���ֽ�
	Code         ����������óֲ�Ʒ�ִ���ķ�������,������ռ�������Ҫ10���ֽ�
	Market       ����������óֲ�Ʒ���г�
	����ֵ��      �ɹ�����1��ʧ�ܷ���0
	*/
	virtual BOOL OrderInfo(UINT Index, int &OrderID, int &ConSign, int &Filled, int &Remaining, int &Action, int &OrderType, double &LmtPrice, double &auxPrice, char *szAccount, char *szCode, WORD &Market) = 0;
	
	/*ȡָ������0������δ�ɽ������ʻ�(CTP,���˴��������Ʊ��)��Լ��Ϣ
	Index        ���������ָ������0�����ĳֲֺ�Լ��Ϣ���ֲֺ�Լ�����μ� OrderNum2 ���ԡ�
	OrderID      �������, δ�ɽ�����ID
	ConSign      �������������ί������
	Filled       ����������ѳɽ�����
	Remaining    ���������δ�ɽ�����
	Action       ����������������� 0���� 1����
	OrderType    ����������������� 0�޼� 1�м� 2ͣ�� 3�м�ͣ��
	LmtPrice     �����������OrderType����0ʱΪ�޼ۣ�Ϊ3ʱΪͣ���޼�
	Account      ����������ʻ���Ϣ����,������ռ�������Ҫ32���ֽ�
	Kaiping      �����������ƽ������ 0���� 1ƽ��
	Code         ����������óֲ�Ʒ�ִ���ķ�������,������ռ�������Ҫ10���ֽ�
	Market       ����������óֲ�Ʒ���г�
	����ֵ��      �ɹ�����1��ʧ�ܷ���0 */	
	virtual BOOL OrderInfo2(UINT Index, int &OrderID, int &ConSign, int &Filled, int &Remaining, int &Action, int &OrderType, double &LmtPrice, char *szAccount, int &Kaiping, char *szCode, WORD &Market) = 0;
	
	/*��ȡָ��Ʒ�ֵĺ�Լ����
	Code         ���������ָ����Ʒ�ִ���
	Market       ���������ָ����Ʒ���г�
	����ֵ���ǿ��Խ��׵ķ�IB���̽ӿ�Ʒ�ַ���1��IB�ӿڷ���0*/
	virtual int StockType(char * szCode, WORD wMarket)  = 0;

	/*ȡָ��Ʒ�ֵĺ�Լ��Ϣ
	Code         ���������ָ����Ʒ�ִ���
	Market       ���������ָ����Ʒ���г�
	Multipliter  �����������Ʒ�ֵĳ���/��λ
	MinTick      �����������Ʒ�ֵ���С�䶯��λ
	ShortPercent �����������Ʒ�ֵĿ�ͷ��֤��
	LongPercent  �����������Ʒ�ֵĶ�ͷ��֤�� 
	����ֵ���ɹ�����1���򷵻�0		
	*/
	virtual int GetContract(char *szCode, WORD wMarket, float &Multipliter, float &MinTick, float &ShortPercent, float &LongPercent) = 0;
	
	/*����ָ��Ʒ�ֵı��ν����������á����û��ڽ��׷���������Ԥ�����úò�ͬƷ�ֵĸ��ֽ��׷����������������ͨ���˷����õ���ȷ�Ľ����
	Code         ָ����Ʒ�ִ���
	Market       ָ����Ʒ���г�
	lmtPrice     ָ�����޼�
	Volume       ί������
	Type         �ɽ����� 0���� 1ƽ�� 2ƽ��
	����ֵ��      ���ؼ�������������*/
	virtual float GetChargeByNum(char * szCode, WORD wMarket, float lmtPrice, int Volume, int Type) = 0;
	
	/*ȡָ������0������ŵ�IB�ʻ��ɽ���ϸ
	Index        �������������0�����ĳɽ���ϸ
	Date         ����������ɽ�ʱ��
	Code         ����������óֲ�Ʒ�ִ���ķ�������,������ռ�������Ҫ10���ֽ�
	Market       ���������Ʒ���г�
	OrderType    ����������ɽ������ͣ�0�޼� 1�м� 2ͣ�� 3�޼�ͣ��
	Action       ����������ɽ����� 0���� 1����
	Price        ����������ɽ��۸�
	Volume       ����������ɽ���
	Account      ����������ʻ���Ϣ����,������ռ�������Ҫ32���ֽ�
	����ֵ��      �ɹ�����1��ʧ�ܷ���0*/
	virtual int TradeDetalied(int Index, DATE &Date, char *szCode, WORD &Market, int &OrderType, int &Action, float &Price, int &Volume, char *szAccount) = 0;
	
	/*ȡָ������0������ŵ������ʻ�(CTP,���˴��������Ʊ��)�ʻ��ɽ���ϸ
	Index        �������������0�����ĳɽ���ϸ
	Date         ����������ɽ�ʱ��
	Code         ����������óֲ�Ʒ�ִ���ķ�������,������ռ�������Ҫ10���ֽ�
	Market       ���������Ʒ���г�
	OrderType    ����������ɽ������ͣ�0�޼� 1�м� 2ͣ�� 3�޼�ͣ��
	Action       ����������ɽ����� 0���� 1����
	Price        ����������ɽ��۸�
	Volume       ����������ɽ���
	Kaiping      �����������ƽ�����ͣ�0���� 1ƽ��
	Account      ����������ɽ��ʻ�����ʡ�ԣ���ʡ�����ʾ��ǰĬ�ϼ����ʻ�
	����ֵ��      �ɹ�����1��ʧ�ܷ���0*/
	virtual int TradeDetalied2(int Index, DATE &Date, char *szCode, WORD &Market, int &OrderType, int &Action, float &Price, int &Volume, int &Kaiping, char *szAccount) = 0;
	
	//�õ�ָ������0������IB�ʻ����ƣ�����IBAccountName��0����ʾȡ��һ����½��IB�ʻ�	
	//nIndex	�������������0������IB��¼�˻�����
	//szAccont  �������,�ʻ���Ϣ����,������ռ�������Ҫ32���ֽ�
	//����ֵ    �ɹ�����true,���򷵻� false
	virtual bool GetIBAccountName(int nIndex, char * szAccount) = 0;
	
	//�õ�ָ������0�����������ʻ�(CTP,���˴��������Ʊ��)�ʻ����ƣ�������½δ�ɹ��ģ������� CTPAccountName��0����ʾȡ��һ����½���û�����	
	//nIndex	�������������0������IB��¼�˻�����
	//szAccont  �������,�ʻ���Ϣ����,������ռ�������Ҫ32���ֽ�
	//����ֵ    �ɹ�����true,���򷵻� false
	virtual bool GetCTPAccountName(int nIndex, char * szAccount) = 0;
	
	//�ж�ָ���ʺ��Ƿ��ǵ�ǰ�ѵ�¼��Ч�ʺţ����� Order.IsAccount("351579")��������˻��ѵ�¼�򷵻�1�����򷵻�0	
	virtual int IsAccount(char *szAccount) = 0;

	//��ȡָ��Ʒ�ֵĶ�̬����
	//	Code         ָ����Ʒ�ִ���
	//	Market       ָ����Ʒ���г�
	//  nType		 ��̬Ʒ�ֵ��������ͣ�����ʹ����ο�PEL���Ե�DYNAINFO���������Ͳ���
	//               �ο� http://www.weistock.com/WeisoftHelp/fulua_dynainfo.htm
	//  ����ֵ		 ���ؼ������ָ��ֵ��������ʧ�ܣ��򷵻���Чֵ
	virtual float GetDynainfo(char * szCode, WORD wMarket, int nType) = 0;

	//��չ���ݽӿڣ���������ӿ�ʵ��δ���Ľӿڹ�������
	virtual void * ExpandFunction(void * pSt, int nType) = 0;
	

	//////////////////////////////////////////////////////////////////////////
	//						��Ȩ�������Ϣ
	//////////////////////////////////////////////////////////////////////////

	//��ȡ��ȨƷ�ֵ�����ֵ
	//	Code         ָ����Ʒ�ִ���
	//	Market       ָ����Ʒ���г�
	//  nType		 ��̬Ʒ�ֵ��������ͣ�����ʹ����ο� http://www.weistock.com/WeisoftHelp/fulua_optioninfo.htm
	//  ����ֵ		 ���ؼ������ָ��ֵ
	virtual VARIANT OptionInfo(char * szCode, WORD wMarket, int nType) = 0;
};

#endif