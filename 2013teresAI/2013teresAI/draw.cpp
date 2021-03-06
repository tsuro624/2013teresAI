#include "Data.h"

void draw(int stage[WIDTH][HEIGHT],AI_T ai[AI_NUM],Tagger tagger,Takara takara){
	int view=0;
	if(CheckHitKey(KEY_INPUT_V))view=1;// 8/19 zero:Vキーを押していると描画モードが変わります。
	static int stageGraph = LoadGraph("Stage_image\\kabe0.png"); //壁の画像読み込み
	//数列stageにしたがってマップの描画
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			if(view==0)SetDrawBright(150,150,150);// 8/19 zero: 薄暗く描写するよう設定
			for(int k=0;k<AI_NUM;k++){// 8/19 zero: AIの視界のみ明るくなるように
				if(i>=ai[k].x-VISIBLE && i<=ai[k].x+VISIBLE && j>=ai[k].y-VISIBLE && j<=ai[k].y+VISIBLE && ai[k].entry==1){
					SetDrawBright(255,255,255);
				}
			}
			if(i==WIDTH/2 || j==HEIGHT/2){//7/27 zero: 十字回廊を描いてちょっとお洒落に
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(100,100,250),0);
			}
			if(stage[i][j]==1){//壁を仮に白い正方形としています。//土の壁にしました。
//				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(255,255,255),1);//四角の描写
				DrawRotaGraph((20*i)+10,(20*j)+10,1.0,0.0,stageGraph,FALSE,FALSE);//読み込んだ壁画像表示
			}
			if(stage[i][j]==4&&takara.drop==0){
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(255,255,255),1);//宝の描写
			}
		}
	}
	//AIの描画
	for(int i=0;i<AI_NUM;i++){
		if(ai[i].entry==1){
			SetDrawBright(255,255,255);
			DrawRotaGraph(ai[i].s_x,ai[i].s_y,1,0,ai[i].Graph,TRUE,FALSE);//読み込んだ画像表示
			//DrawCircle(ai[i].s_x,ai[i].s_y,5,GetColor(255,0,0),1);//点表示
			if(view==1){
				DrawBox(BOX*ai[i].x,BOX*ai[i].y,BOX*(ai[i].x+1),BOX*(ai[i].y+1),GetColor(255,0,0),0);
				DrawBox(BOX*(ai[i].x-VISIBLE),BOX*(ai[i].y-VISIBLE),BOX*(ai[i].x+VISIBLE+1),BOX*(ai[i].y+VISIBLE+1),GetColor(255,255,255),0);//AIの視界（確認用）
			}
		}
	}
	//鬼の描画
	
	DrawRotaGraph(tagger.s_x,tagger.s_y,0.75,0,tagger.Graph,TRUE,FALSE);//読み込んだ画像表示 //今は青鬼が出てきて怖いからコメントアウト
	//DrawCircle(tagger.s_x,tagger.s_y,20,GetColor(0,0,255),1);
	if(view==1)DrawBox(BOX*tagger.x,BOX*tagger.y,BOX*(tagger.x+1),BOX*(tagger.y+1),GetColor(255,0,0),0);
	
	//AI名の描画

	for(int i=0;i<AI_NUM;i++){
		if(ai[i].entry==1){
			static int flash=0;
			int cr;
			flash++;
			cr=GetColor(255,255*(flash%3),255*(flash%4));
			DrawFormatString(ai[i].s_x,ai[i].s_y,cr,ai[i].name);
		}
	}
	
	//マップデータ表示
	while(CheckHitKey(KEY_INPUT_P)==1){
		int ai_x[AI_NUM],ai_y[AI_NUM],ai_num=0;
		DrawBox(0,0,640,480,GetColor(0,0,0),1);
		for(int i=0;i<WIDTH;i++){
			for(int j=0;j<HEIGHT;j++){
				int cr;
				switch(stage[i][j]){
				case 1:
					cr=GetColor(100,50,0);
					break;
				case 2:
					cr=GetColor(255,0,0);
					ai_x[ai_num]=i;
					ai_y[ai_num]=j;
					ai_num++;
					break;
				case 3:
					cr=GetColor(0,0,100);
					break;
				default:
					cr=GetColor(0,0,0);
					break;
				}
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),cr,1);
				cr=GetColor(255,255,255);
				//DrawBox(20*i,20*j,20*(i+1),20*(j+1),cr,0);
				DrawFormatString(i*20+5,j*20+5,cr,"%d",stage[i][j]);
				
			}
		}
		for(int i=0;i<AI_NUM;i++){
			DrawBox(20*(ai_x[i]-10),20*(ai_y[i]-10),20*(ai_x[i]+10),20*(ai_y[i]+10),GetColor(255,255,0),0);
		}
		/*
		for(int i=0;i<AI_NUM;i++){
			for(int w=0;w<2*VISIBLE+1;w++){
				for(int h=0;h<2*VISIBLE+1;h++){
					int cx=20*ai[i].x+(w-VISIBLE)*20,cy=20*ai[i].y+(h-VISIBLE)*20;
					DrawFormatString(cx,cy,GetColor(255,255,255),"%d",ai[i].view[w][h]);
				}
			}
		}*/
		WaitTimer(100);
	}
	
	//鬼が手動か自動か表示
    char Buf[ 256 ] ;
	GetHitKeyStateAll( Buf ) ;
	if( Buf[ KEY_INPUT_A ] == 1 ) {
		const char* str = strcat(tagger.name , "鬼手動モード"); //文字列連結
		DrawString( 15, 15, str ,GetColor(255,0,255) );
	}else {
		const char* str = strcat(tagger.name , "鬼AIモード"); //文字列連結
		DrawString( 15, 15, str ,GetColor(255,0,255) );
	}
}