#pragma once
#include <string>

namespace NativeWinGUIC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::TextBox^ tbReactants;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::CheckBox^ ckbRecombination;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ListBox^ lstbRecombOptions;


	private: System::Windows::Forms::TextBox^ tbPressure;



	private: System::Windows::Forms::Button^ btnRun;





	private: System::Windows::Forms::Button^ btnClear;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ tbProducts;




	private: System::Windows::Forms::Label^ label10;



	private: System::Windows::Forms::Label^ label11;



	private: System::Windows::Forms::RadioButton^ rdbOutK;
	private: System::Windows::Forms::RadioButton^ rdbOutC;
	private: System::Windows::Forms::RadioButton^ rdbOutF;



	private: System::Windows::Forms::RadioButton^ rdbPressurePSI;
	private: System::Windows::Forms::RadioButton^ rdbPressureKPA;
	private: System::Windows::Forms::RadioButton^ rdbPressureATM;

	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::RadioButton^ rdbLogFULL;
	private: System::Windows::Forms::RadioButton^ rdbLogSIMPLE;
	private: System::Windows::Forms::RadioButton^ rdbLogDEBUG;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::GroupBox^ groupBox4;

	private: System::Windows::Forms::Button^ btnHelp;



	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label15;



	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;




	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::Label^ label21;


	private: System::Windows::Forms::Label^ label26;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label14;



	private: System::ComponentModel::IContainer^ components;








	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tbReactants = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->ckbRecombination = (gcnew System::Windows::Forms::CheckBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lstbRecombOptions = (gcnew System::Windows::Forms::ListBox());
			this->tbPressure = (gcnew System::Windows::Forms::TextBox());
			this->btnRun = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tbProducts = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->rdbOutK = (gcnew System::Windows::Forms::RadioButton());
			this->rdbOutC = (gcnew System::Windows::Forms::RadioButton());
			this->rdbOutF = (gcnew System::Windows::Forms::RadioButton());
			this->rdbPressurePSI = (gcnew System::Windows::Forms::RadioButton());
			this->rdbPressureKPA = (gcnew System::Windows::Forms::RadioButton());
			this->rdbPressureATM = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->rdbLogDEBUG = (gcnew System::Windows::Forms::RadioButton());
			this->rdbLogSIMPLE = (gcnew System::Windows::Forms::RadioButton());
			this->rdbLogFULL = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->btnHelp = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(235, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(211, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Adiabatic Flame Temperature Calculator V1";
			// 
			// tbReactants
			// 
			this->tbReactants->ForeColor = System::Drawing::Color::Gray;
			this->tbReactants->Location = System::Drawing::Point(9, 44);
			this->tbReactants->Name = L"tbReactants";
			this->tbReactants->Size = System::Drawing::Size(247, 20);
			this->tbReactants->TabIndex = 2;
			this->tbReactants->Text = L"e.g. N2H4 3N2 H2";
			this->tbReactants->Enter += gcnew System::EventHandler(this, &MainForm::tbReactants_Enter);
			this->tbReactants->Leave += gcnew System::EventHandler(this, &MainForm::tbReactants_Leave);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 126);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(163, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Consider Recombination effects\?";
			// 
			// ckbRecombination
			// 
			this->ckbRecombination->AutoSize = true;
			this->ckbRecombination->Location = System::Drawing::Point(179, 126);
			this->ckbRecombination->Name = L"ckbRecombination";
			this->ckbRecombination->Size = System::Drawing::Size(15, 14);
			this->ckbRecombination->TabIndex = 4;
			this->ckbRecombination->UseVisualStyleBackColor = true;
			this->ckbRecombination->CheckedChanged += gcnew System::EventHandler(this, &MainForm::ckbRecombination_CheckedChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 148);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(67, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Which One\?";
			// 
			// lstbRecombOptions
			// 
			this->lstbRecombOptions->FormattingEnabled = true;
			this->lstbRecombOptions->Items->AddRange(gcnew cli::array< System::Object^  >(17) {
				L"O = O2", L"H = H2", L"OH = O2 + H2",
					L"H2O = H2 + O2", L"N = N2", L"NO = N2 + O2", L"CO = C + O2", L"CO2 = C + O2", L"CH4 = C + H2", L"C2H2 = C + H2", L"Cl = Cl2",
					L"HCl = H2 + Cl2", L"NH = N2 + H2", L"NH3 = N2 + H2", L"CH2 = C + H2", L"NO2 = NO + O2", L"NO = N2 + O2"
			});
			this->lstbRecombOptions->Location = System::Drawing::Point(9, 164);
			this->lstbRecombOptions->Name = L"lstbRecombOptions";
			this->lstbRecombOptions->SelectionMode = System::Windows::Forms::SelectionMode::MultiSimple;
			this->lstbRecombOptions->Size = System::Drawing::Size(182, 69);
			this->lstbRecombOptions->TabIndex = 6;
			this->lstbRecombOptions->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::lstbRecombOptions_SelectedIndexChanged);
			// 
			// tbPressure
			// 
			this->tbPressure->Location = System::Drawing::Point(6, 19);
			this->tbPressure->Name = L"tbPressure";
			this->tbPressure->Size = System::Drawing::Size(140, 20);
			this->tbPressure->TabIndex = 8;
			// 
			// btnRun
			// 
			this->btnRun->Location = System::Drawing::Point(405, 328);
			this->btnRun->Name = L"btnRun";
			this->btnRun->Size = System::Drawing::Size(297, 23);
			this->btnRun->TabIndex = 12;
			this->btnRun->Text = L"Run";
			this->btnRun->UseVisualStyleBackColor = true;
			this->btnRun->Click += gcnew System::EventHandler(this, &MainForm::btnRun_Click);
			// 
			// btnClear
			// 
			this->btnClear->AutoSize = true;
			this->btnClear->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->btnClear->Location = System::Drawing::Point(238, 328);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(55, 23);
			this->btnClear->TabIndex = 13;
			this->btnClear->Text = L"Clear All";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &MainForm::btnClear_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 28);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(56, 13);
			this->label6->TabIndex = 14;
			this->label6->Text = L"Reactants";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 72);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(49, 13);
			this->label7->TabIndex = 15;
			this->label7->Text = L"Products";
			// 
			// tbProducts
			// 
			this->tbProducts->ForeColor = System::Drawing::Color::Gray;
			this->tbProducts->Location = System::Drawing::Point(9, 88);
			this->tbProducts->Name = L"tbProducts";
			this->tbProducts->Size = System::Drawing::Size(247, 20);
			this->tbProducts->TabIndex = 16;
			this->tbProducts->Text = L"e.g. 2NH3 N2 H2";
			this->tbProducts->Enter += gcnew System::EventHandler(this, &MainForm::tbProducts_Enter);
			this->tbProducts->Leave += gcnew System::EventHandler(this, &MainForm::tbProducts_Leave);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(9, 25);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(94, 13);
			this->label10->TabIndex = 19;
			this->label10->Text = L"Temperature Units";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(3, 2);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(25, 13);
			this->label11->TabIndex = 23;
			this->label11->Text = L"Log";
			// 
			// rdbOutK
			// 
			this->rdbOutK->AutoSize = true;
			this->rdbOutK->Checked = true;
			this->rdbOutK->Location = System::Drawing::Point(120, 23);
			this->rdbOutK->Name = L"rdbOutK";
			this->rdbOutK->Size = System::Drawing::Size(32, 17);
			this->rdbOutK->TabIndex = 27;
			this->rdbOutK->TabStop = true;
			this->rdbOutK->Text = L"K";
			this->rdbOutK->UseVisualStyleBackColor = true;
			this->rdbOutK->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rdbOutK_CheckedChanged);
			// 
			// rdbOutC
			// 
			this->rdbOutC->AutoSize = true;
			this->rdbOutC->Location = System::Drawing::Point(159, 23);
			this->rdbOutC->Name = L"rdbOutC";
			this->rdbOutC->Size = System::Drawing::Size(36, 17);
			this->rdbOutC->TabIndex = 28;
			this->rdbOutC->Text = L"°C";
			this->rdbOutC->UseVisualStyleBackColor = true;
			this->rdbOutC->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rdbOutC_CheckedChanged);
			// 
			// rdbOutF
			// 
			this->rdbOutF->AutoSize = true;
			this->rdbOutF->Location = System::Drawing::Point(202, 23);
			this->rdbOutF->Name = L"rdbOutF";
			this->rdbOutF->Size = System::Drawing::Size(35, 17);
			this->rdbOutF->TabIndex = 29;
			this->rdbOutF->Text = L"°F";
			this->rdbOutF->UseVisualStyleBackColor = true;
			this->rdbOutF->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rdbOutF_CheckedChanged);
			// 
			// rdbPressurePSI
			// 
			this->rdbPressurePSI->AutoSize = true;
			this->rdbPressurePSI->Location = System::Drawing::Point(6, 45);
			this->rdbPressurePSI->Name = L"rdbPressurePSI";
			this->rdbPressurePSI->Size = System::Drawing::Size(38, 17);
			this->rdbPressurePSI->TabIndex = 30;
			this->rdbPressurePSI->Text = L"psi";
			this->rdbPressurePSI->UseVisualStyleBackColor = true;
			this->rdbPressurePSI->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rdbPressurePSI_CheckedChanged);
			// 
			// rdbPressureKPA
			// 
			this->rdbPressureKPA->AutoSize = true;
			this->rdbPressureKPA->Location = System::Drawing::Point(54, 45);
			this->rdbPressureKPA->Name = L"rdbPressureKPA";
			this->rdbPressureKPA->Size = System::Drawing::Size(44, 17);
			this->rdbPressureKPA->TabIndex = 31;
			this->rdbPressureKPA->Text = L"kPa";
			this->rdbPressureKPA->UseVisualStyleBackColor = true;
			this->rdbPressureKPA->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rdbPressureKPA_CheckedChanged);
			// 
			// rdbPressureATM
			// 
			this->rdbPressureATM->AutoSize = true;
			this->rdbPressureATM->Checked = true;
			this->rdbPressureATM->Location = System::Drawing::Point(104, 45);
			this->rdbPressureATM->Name = L"rdbPressureATM";
			this->rdbPressureATM->Size = System::Drawing::Size(42, 17);
			this->rdbPressureATM->TabIndex = 32;
			this->rdbPressureATM->TabStop = true;
			this->rdbPressureATM->Text = L"atm";
			this->rdbPressureATM->UseVisualStyleBackColor = true;
			this->rdbPressureATM->CheckedChanged += gcnew System::EventHandler(this, &MainForm::rdbPressureATM_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rdbPressureATM);
			this->groupBox1->Controls->Add(this->tbPressure);
			this->groupBox1->Controls->Add(this->rdbPressureKPA);
			this->groupBox1->Controls->Add(this->rdbPressurePSI);
			this->groupBox1->Location = System::Drawing::Point(15, 309);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(169, 70);
			this->groupBox1->TabIndex = 33;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Reaction Pressure Input";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->panel1);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->rdbOutF);
			this->groupBox2->Controls->Add(this->rdbOutC);
			this->groupBox2->Controls->Add(this->rdbOutK);
			this->groupBox2->Location = System::Drawing::Point(405, 57);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(297, 76);
			this->groupBox2->TabIndex = 34;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Output Settings";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->rdbLogDEBUG);
			this->panel1->Controls->Add(this->rdbLogSIMPLE);
			this->panel1->Controls->Add(this->rdbLogFULL);
			this->panel1->Controls->Add(this->label11);
			this->panel1->Location = System::Drawing::Point(6, 45);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(285, 25);
			this->panel1->TabIndex = 36;
			// 
			// rdbLogDEBUG
			// 
			this->rdbLogDEBUG->AutoSize = true;
			this->rdbLogDEBUG->Location = System::Drawing::Point(208, 0);
			this->rdbLogDEBUG->Name = L"rdbLogDEBUG";
			this->rdbLogDEBUG->Size = System::Drawing::Size(57, 17);
			this->rdbLogDEBUG->TabIndex = 32;
			this->rdbLogDEBUG->Text = L"Debug";
			this->rdbLogDEBUG->UseVisualStyleBackColor = true;
			// 
			// rdbLogSIMPLE
			// 
			this->rdbLogSIMPLE->AutoSize = true;
			this->rdbLogSIMPLE->Checked = true;
			this->rdbLogSIMPLE->Location = System::Drawing::Point(97, 0);
			this->rdbLogSIMPLE->Name = L"rdbLogSIMPLE";
			this->rdbLogSIMPLE->Size = System::Drawing::Size(56, 17);
			this->rdbLogSIMPLE->TabIndex = 30;
			this->rdbLogSIMPLE->TabStop = true;
			this->rdbLogSIMPLE->Text = L"Simple";
			this->rdbLogSIMPLE->UseVisualStyleBackColor = true;
			// 
			// rdbLogFULL
			// 
			this->rdbLogFULL->AutoSize = true;
			this->rdbLogFULL->Location = System::Drawing::Point(160, 0);
			this->rdbLogFULL->Name = L"rdbLogFULL";
			this->rdbLogFULL->Size = System::Drawing::Size(41, 17);
			this->rdbLogFULL->TabIndex = 31;
			this->rdbLogFULL->Text = L"Full";
			this->rdbLogFULL->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->tbReactants);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->ckbRecombination);
			this->groupBox3->Controls->Add(this->tbProducts);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->lstbRecombOptions);
			this->groupBox3->Location = System::Drawing::Point(15, 57);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(312, 240);
			this->groupBox3->TabIndex = 35;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Chemical Reaction Input";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->tableLayoutPanel1);
			this->groupBox4->Location = System::Drawing::Point(405, 145);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(297, 152);
			this->groupBox4->TabIndex = 36;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Available Compounds";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 8;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				56)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				89)));
			this->tableLayoutPanel1->Controls->Add(this->label18, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->label26, 6, 5);
			this->tableLayoutPanel1->Controls->Add(this->label17, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->label24, 5, 5);
			this->tableLayoutPanel1->Controls->Add(this->label25, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->label23, 1, 5);
			this->tableLayoutPanel1->Controls->Add(this->label2, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label5, 5, 0);
			this->tableLayoutPanel1->Controls->Add(this->label8, 6, 0);
			this->tableLayoutPanel1->Controls->Add(this->label22, 7, 4);
			this->tableLayoutPanel1->Controls->Add(this->label9, 7, 0);
			this->tableLayoutPanel1->Controls->Add(this->label21, 6, 4);
			this->tableLayoutPanel1->Controls->Add(this->label12, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->label20, 5, 4);
			this->tableLayoutPanel1->Controls->Add(this->label13, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->label19, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->label14, 5, 3);
			this->tableLayoutPanel1->Controls->Add(this->label15, 6, 3);
			this->tableLayoutPanel1->Controls->Add(this->label16, 7, 3);
			this->tableLayoutPanel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tableLayoutPanel1->Location = System::Drawing::Point(27, 19);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 6;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 18)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 22)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(244, 116);
			this->tableLayoutPanel1->TabIndex = 20;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(3, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(35, 17);
			this->label18->TabIndex = 11;
			this->label18->Text = L"CH4";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(137, 52);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(37, 17);
			this->label26->TabIndex = 19;
			this->label26->Text = L"NO2";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(3, 34);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(36, 17);
			this->label17->TabIndex = 10;
			this->label17->Text = L"CO2";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(95, 52);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(36, 17);
			this->label24->TabIndex = 17;
			this->label24->Text = L"NH3";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(3, 52);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(35, 17);
			this->label25->TabIndex = 18;
			this->label25->Text = L"CH2";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(46, 52);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(28, 17);
			this->label23->TabIndex = 16;
			this->label23->Text = L"NH";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(46, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(27, 17);
			this->label2->TabIndex = 1;
			this->label2->Text = L"O2";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(95, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(18, 17);
			this->label5->TabIndex = 2;
			this->label5->Text = L"H";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(137, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(26, 17);
			this->label8->TabIndex = 3;
			this->label8->Text = L"H2";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(193, 34);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(30, 17);
			this->label22->TabIndex = 15;
			this->label22->Text = L"HCl";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(193, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(29, 17);
			this->label9->TabIndex = 4;
			this->label9->Text = L"OH";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(137, 34);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(28, 17);
			this->label21->TabIndex = 14;
			this->label21->Text = L"Cl2";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(3, 17);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(37, 17);
			this->label12->TabIndex = 5;
			this->label12->Text = L"H2O";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(95, 34);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(20, 17);
			this->label20->TabIndex = 13;
			this->label20->Text = L"Cl";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(46, 17);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(18, 17);
			this->label13->TabIndex = 6;
			this->label13->Text = L"N";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(46, 34);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(43, 17);
			this->label19->TabIndex = 12;
			this->label19->Text = L"C2H2";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(95, 17);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(26, 17);
			this->label14->TabIndex = 7;
			this->label14->Text = L"N2";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(137, 17);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(29, 17);
			this->label15->TabIndex = 8;
			this->label15->Text = L"NO";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(193, 17);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(28, 17);
			this->label16->TabIndex = 9;
			this->label16->Text = L"CO";
			// 
			// btnHelp
			// 
			this->btnHelp->Location = System::Drawing::Point(598, 9);
			this->btnHelp->Name = L"btnHelp";
			this->btnHelp->Size = System::Drawing::Size(104, 23);
			this->btnHelp->TabIndex = 37;
			this->btnHelp->Text = L"How to use this\?";
			this->btnHelp->UseVisualStyleBackColor = true;
			this->btnHelp->Click += gcnew System::EventHandler(this, &MainForm::btnHelp_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(714, 391);
			this->Controls->Add(this->btnHelp);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnRun);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"Adiabatic Flame Temperature Calculator";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}


	private: System::Void tbReactants_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (tbReactants->Text == "e.g. N2H4 3N2 H2")
		{
			tbReactants->Text = "";
			tbReactants->ForeColor = System::Drawing::Color::Black;
		}
	}
	private: System::Void tbReactants_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrWhiteSpace(tbReactants->Text))
		{
			tbReactants->Text = "e.g. N2H4 3N2 H2";
			tbReactants->ForeColor = System::Drawing::Color::Gray;
		}
	}

	private: System::Void tbProducts_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (tbProducts->Text == "e.g. 2NH3 N2 H2")
		{
			tbProducts->Text = "";
			tbProducts->ForeColor = System::Drawing::Color::Black;
		}
	}
	private: System::Void tbProducts_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrWhiteSpace(tbProducts->Text))
		{
			tbProducts->Text = "e.g. 2NH3 N2 H2";
			tbProducts->ForeColor = System::Drawing::Color::Gray;
		}
	}
		   

	

	private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e) {
		this->tbReactants->Text = "";
		this->tbProducts->Text = "";
		this->tbPressure->Text = "";
		this->ckbRecombination->Checked = 0;
		this->lstbRecombOptions->SelectedIndex = -1;
	}


	private: System::Void ckbRecombination_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lstbRecombOptions_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void rdbPressurePSI_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void rdbPressureKPA_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void rdbPressureATM_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void rdbOutK_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void rdbOutC_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void rdbOutF_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnRun_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void btnHelp_Click(System::Object^ sender, System::EventArgs^ e);



};
}
