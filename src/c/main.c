#include <pebble.h>

// Magic numbers
#define SCREEN_WIDTH        144
#define SCREEN_HEIGHT       168

#define RIGA_WIDTH          144
#define RIGA_HEIGHT         56

// Images
#define NUMBER_OF_ORE_IMAGES 13
const int le_ore_array[NUMBER_OF_ORE_IMAGES] = { 0,
  RESOURCE_ID_le_h_1, RESOURCE_ID_le_h_2, RESOURCE_ID_le_h_3, RESOURCE_ID_le_h_4, 
  RESOURCE_ID_le_h_5, RESOURCE_ID_le_h_6, RESOURCE_ID_le_h_7, RESOURCE_ID_le_h_8, 
  RESOURCE_ID_le_h_9, RESOURCE_ID_le_h_10, RESOURCE_ID_le_h_11, RESOURCE_ID_le_h_12
};

const int ore_array[NUMBER_OF_ORE_IMAGES] = { 0,
  RESOURCE_ID_h_1, RESOURCE_ID_h_2, RESOURCE_ID_h_3, RESOURCE_ID_h_4, 
  RESOURCE_ID_h_5, RESOURCE_ID_h_6, RESOURCE_ID_h_7, RESOURCE_ID_h_8, 
  RESOURCE_ID_h_9, RESOURCE_ID_h_10, RESOURCE_ID_h_11, RESOURCE_ID_h_12
};

#define NUMBER_OF_MISC_IMAGES 55
const int immagini[NUMBER_OF_MISC_IMAGES] = {
  RESOURCE_ID_alle, RESOURCE_ID_circa, RESOURCE_ID_da_poco, RESOURCE_ID_e, 
  RESOURCE_ID_e_dieci, RESOURCE_ID_e_mezza, RESOURCE_ID_e_mezzo, RESOURCE_ID_e_quaranta, 
  RESOURCE_ID_e_tre_quarti, RESOURCE_ID_e_un_quarto, RESOURCE_ID_e_venti, RESOURCE_ID_meno, 
  RESOURCE_ID_meno_dieci, RESOURCE_ID_meno_venti, RESOURCE_ID_mezza, RESOURCE_ID_mezzo, 
  RESOURCE_ID_nera, RESOURCE_ID_passate, RESOURCE_ID_poco_dopo, RESOURCE_ID_qualcosa, 
  RESOURCE_ID_quaranta, RESOURCE_ID_quasi, RESOURCE_ID_tre_quarti, RESOURCE_ID_un_quarto, 
  RESOURCE_ID_venti, RESOURCE_ID_tipo, RESOURCE_ID_piu_o_meno, RESOURCE_ID_notte, RESOURCE_ID_dormi, 
  RESOURCE_ID_amore, RESOURCE_ID_secondo_me, RESOURCE_ID_sono_tipo, RESOURCE_ID_credo_siano, RESOURCE_ID_saranno,
  RESOURCE_ID_e_qualcosa, RESOURCE_ID_fra_poco, RESOURCE_ID_ora_di, RESOURCE_ID_farsi, RESOURCE_ID_birretta,
  RESOURCE_ID_ora_di_ieri, RESOURCE_ID_a_quest_ora, RESOURCE_ID_rimpiangere, RESOURCE_ID_ferie,
  RESOURCE_ID_cellulare, RESOURCE_ID_dove_lo_hai, RESOURCE_ID_lasciato,
  RESOURCE_ID_mollato, RESOURCE_ID_infilato, RESOURCE_ID_perso, RESOURCE_ID_birretta_pi,
  RESOURCE_ID_caffeino, RESOURCE_ID_caffeino_pi, RESOURCE_ID_dai_che, RESOURCE_ID_ce_la_fai,
  RESOURCE_ID_tergiversare
};

int ore;
int minuti;
//int righe[3];
bool quasi;

// General
static Window *window;


#define EMPTY_SLOT -1
typedef struct Slot {
  int         number;
  GBitmap     *image;
  BitmapLayer *image_layer;
  int         state;
} Slot;

// Time
typedef struct TimeSlot {
  int               immagine;
  Slot              slot;
  int               new_state;
  bool              updating;
} TimeSlot;

#define NUMBER_OF_TIME_SLOTS 3
static Layer *time_layer;
static TimeSlot righe[NUMBER_OF_TIME_SLOTS];

double random()
{
    return (double)rand() / (double)RAND_MAX ;
}


void setCinqueCinque(int ore){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
  double r = random();
  if(r <= 0.25){
		rzero->immagine = RESOURCE_ID_quasi;
	  runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.5){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.75){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else{
		rzero->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
		runo->immagine = RESOURCE_ID_meno;
		rdue->immagine = RESOURCE_ID_qualcosa;
    return;
	}
}

void setCinque(int ore){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(r <= 0.2){
		rzero->immagine = le_ore_array[ore];
    runo->immagine = RESOURCE_ID_nera;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.4){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_qualcosa;
    return;
	}else if(r <= 0.6){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.8){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else{
		rzero->immagine = RESOURCE_ID_circa;
		runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}
}

void setOtto(int ore){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(r <= 0.33){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_qualcosa;
    return;
	}else if(r <= 0.66){
		rzero->immagine = RESOURCE_ID_poco_dopo;
		runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else{
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_passate;
		rdue->immagine = RESOURCE_ID_da_poco;
    return;
	}
}

void setDieci(int ore, bool quasi){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(quasi){
    if(r <= 0.5){
  		rzero->immagine = RESOURCE_ID_circa;
  		runo->immagine = le_ore_array[ore];
      rdue->immagine = RESOURCE_ID_e_dieci;
      return;
  	}else{
  		rzero->immagine = RESOURCE_ID_quasi;
  		runo->immagine = le_ore_array[ore];
  		rdue->immagine = RESOURCE_ID_e_dieci;
      return;
    }
	}else if(r <= 0.2){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_dieci;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.4 && minuti > 10){
		rzero->immagine = RESOURCE_ID_poco_dopo;
		runo->immagine = le_ore_array[ore];
		rdue->immagine = RESOURCE_ID_e_dieci;
    return;
	}else if(r <= 0.6){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_dieci;
    return;
	}else if(r <= 0.8){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_dieci;
    return;
	}else{
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_h_10;
    return;
	}
}

void setUnQuarto(int ore, bool quasi){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(quasi){
    if(r <= 0.5){
  		rzero->immagine = RESOURCE_ID_circa;
  		runo->immagine = le_ore_array[ore];
  		rdue->immagine = RESOURCE_ID_e_un_quarto;
      return;
  	}else{
  		rzero->immagine = RESOURCE_ID_quasi;
  		runo->immagine = le_ore_array[ore];
  		rdue->immagine = RESOURCE_ID_e_un_quarto;
      return;
    }
	}else if(r <= 0.2){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_un_quarto;
    return;
	}else if(r <= 0.4 && minuti > 15){
		rzero->immagine = RESOURCE_ID_poco_dopo;
		runo->immagine = le_ore_array[ore];
		rdue->immagine = RESOURCE_ID_un_quarto;
    return;
	}else if(r <= 0.6){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_un_quarto;
    return;
	}else if(r <= 0.8){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_un_quarto;
    return;
	}else{
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_un_quarto;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}
}

void setVenti(int ore, bool quasi){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(quasi){
		if(r <= 0.5){
  		rzero->immagine = RESOURCE_ID_circa;
  		runo->immagine = le_ore_array[ore];
  		rdue->immagine = RESOURCE_ID_e_venti;
      return;
  	}else{
  		rzero->immagine = RESOURCE_ID_quasi;
  		runo->immagine = le_ore_array[ore];
  		rdue->immagine = RESOURCE_ID_e_venti;
      return;
    }
	}else if(r <= 0.2){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_venti;
    return;
	}else if(r <= 0.4 && minuti > 20){
		rzero->immagine = RESOURCE_ID_poco_dopo;
		runo->immagine = le_ore_array[ore];
		rdue->immagine = RESOURCE_ID_e_venti;
    return;
	}else if(r <= 0.6){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_venti;
    return;
	}else if(r <= 0.8){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_venti;
    return;
	}else{
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_venti;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}
}

void setMezza(int ore, bool quasi){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(quasi){
		if(r <= 0.25){
			rzero->immagine = RESOURCE_ID_circa;
			runo->immagine = le_ore_array[ore];
			rdue->immagine = RESOURCE_ID_e_mezzo;
      return;
    }else if(r <= 0.5){
			rzero->immagine = RESOURCE_ID_circa;
			runo->immagine = le_ore_array[ore];
			rdue->immagine = RESOURCE_ID_e_mezza;
      return;
		}else if(r <= 0.75){
			rzero->immagine = RESOURCE_ID_quasi;
			runo->immagine = le_ore_array[ore];
			rdue->immagine = RESOURCE_ID_e_mezzo;
      return;
    }else{
			rzero->immagine = RESOURCE_ID_quasi;
			runo->immagine = le_ore_array[ore];
			rdue->immagine = RESOURCE_ID_e_mezza;
      return;
		}
	}else if(r <= 0.125){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_mezza;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.25){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_mezzo;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.375){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_mezza;
    return;
	}else if(r <= 0.5){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_mezzo;
    return;
	}else if(r <= 0.625){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_mezzo;
    return;
	}else if(r <= 0.75){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_mezza;
    return;
	}else if(r <= 0.875){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_mezza;
    return;
	}else{
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_mezzo;
    return;
	}
}

void setMezzaPassate(int ore){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(r <= 0.33){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_mezza;
		rdue->immagine = RESOURCE_ID_passate;
    return;
	}else if(r <= 0.66){
		rzero->immagine = RESOURCE_ID_poco_dopo;
		runo->immagine = le_ore_array[ore];
		rdue->immagine = RESOURCE_ID_e_mezza;
    return;
	}else{
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_mezzo;
		rdue->immagine = RESOURCE_ID_passate;
    return;
	}
}


void setQuaranta(int ore, bool quasi){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(quasi){
		if(r <= 0.25){
			rzero->immagine = RESOURCE_ID_circa;
			runo->immagine = le_ore_array[ore];
			rdue->immagine = RESOURCE_ID_e_quaranta;
      return;
    }else if(r <= 0.5){
			rzero->immagine = RESOURCE_ID_circa;
			runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
			rdue->immagine = RESOURCE_ID_meno_venti;
      return;
		}else if(r <= 0.75){
			rzero->immagine = RESOURCE_ID_quasi;
			runo->immagine = le_ore_array[ore];
			rdue->immagine = RESOURCE_ID_e_quaranta;
      return;
    }else{
			rzero->immagine = RESOURCE_ID_quasi;
			runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
			rdue->immagine = RESOURCE_ID_meno_venti;
      return;
		}
	}else if(r <= 0.111){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_quaranta;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.222){
		rzero->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
		runo->immagine = RESOURCE_ID_meno_venti;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.333){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_quaranta;
    return;
	}else if(r <= 0.444){
		rzero->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
		runo->immagine = RESOURCE_ID_meno;
		rdue->immagine = RESOURCE_ID_venti;
    return;
	}else if(r <= 0.555){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    rdue->immagine = RESOURCE_ID_meno_venti;
    return;
	}else if(r <= 0.666){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    rdue->immagine = RESOURCE_ID_meno_venti;
    return;
	}else if(r <= 0.777){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_quaranta;
    return;
	}else if(r <= 0.888){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_quaranta;
    return;
	}else{
		rzero->immagine = RESOURCE_ID_venti;
		runo->immagine = RESOURCE_ID_alle;
		rdue->immagine = ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    return;
	}
}

void setTreQuarti(int ore, bool quasi){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(quasi){
		if(r <= 0.5){
  		rzero->immagine = RESOURCE_ID_circa;
  		runo->immagine = le_ore_array[ore];
  		rdue->immagine = RESOURCE_ID_e_tre_quarti;
      return;
  	}else{
  		rzero->immagine = RESOURCE_ID_quasi;
  		runo->immagine = le_ore_array[ore];
  		rdue->immagine = RESOURCE_ID_e_tre_quarti;
      return;
    }
	}else if(r <= 0.166){
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e_tre_quarti;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.332){
		rzero->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
		runo->immagine = RESOURCE_ID_meno;
		rdue->immagine = RESOURCE_ID_un_quarto;
    return;
	}else if(r <= 0.498){
		rzero->immagine = RESOURCE_ID_un_quarto;
		runo->immagine = RESOURCE_ID_alle;
		rdue->immagine = ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    return;
	}else if(r <= 0.664){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_tre_quarti;
    return;
	}else if(r <= 0.83){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[ore];
    rdue->immagine = RESOURCE_ID_e_tre_quarti;
    return;
	}else{
		rzero->immagine = le_ore_array[ore];
		runo->immagine = RESOURCE_ID_e;
		rdue->immagine = RESOURCE_ID_tre_quarti;
    return;
	}
}

void setCinquanta(int ore, bool quasi){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(quasi){
		if(r <= 0.5){
  		rzero->immagine = RESOURCE_ID_circa;
  		runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
  		rdue->immagine = RESOURCE_ID_meno_dieci;
      return;
  	}else{
  		rzero->immagine = RESOURCE_ID_quasi;
  		runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
  		rdue->immagine = RESOURCE_ID_meno_dieci;
      return;
    }
	}else if(r <= 0.2){
		rzero->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
		runo->immagine = RESOURCE_ID_meno_dieci;
    rdue->immagine = RESOURCE_ID_nera;
    return;
	}else if(r <= 0.4){
		rzero->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
		runo->immagine = RESOURCE_ID_meno;
		rdue->immagine = RESOURCE_ID_h_10;
    return;
	}else if(r <= 0.6){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
	  runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    rdue->immagine = RESOURCE_ID_meno_dieci;
    return;
	}else if(r <= 0.8){
		rzero->immagine = RESOURCE_ID_tipo;
	  runo->immagine = le_ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    rdue->immagine = RESOURCE_ID_meno_dieci;
    return;
	}else{
		rzero->immagine = RESOURCE_ID_h_10;
		runo->immagine = RESOURCE_ID_alle;
		rdue->immagine = ore_array[((ore+1 <= 12) ? ore+1 : 1)];
    return;
	}
}




// General
void destroy_property_animation(PropertyAnimation **prop_animation);
void unload_digit_image_from_slot(Slot *slot);

// Time
void display_time(struct tm *tick_time, TimeUnits units_changed);
void display_time_value(int ore, int minuti, bool notte, bool ape, bool caffe);
void update_time_slot(TimeSlot *time_slot, int num_riga);
//GRect frame_for_time_slot(TimeSlot *time_slot);

void setCellulareDisconnesso(){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
  rzero->immagine = RESOURCE_ID_cellulare;
	runo->immagine = RESOURCE_ID_dove_lo_hai;
	double r = random();
	if(r <= 0.25){
		rdue->immagine = RESOURCE_ID_lasciato;
	}else if(r <= 0.5){
		rdue->immagine = RESOURCE_ID_perso;
	}else if(r <= 0.75){
		rdue->immagine = RESOURCE_ID_mollato;
	}else{
		rdue->immagine = RESOURCE_ID_infilato;
	}
  TimeSlot *tsuno = &righe[0];
  update_time_slot(tsuno, 0);
  TimeSlot *tsdue = &righe[1];
  update_time_slot(tsdue, 1);
  TimeSlot *tstre = &righe[2];
  update_time_slot(tstre, 2);
}

static void bluetooth_callback(bool connected) {
  if(!connected) {
    // Issue a vibrating alert
    vibes_double_pulse();
    setCellulareDisconnesso();
  }
}

// Handlers
int main(void);
void init();
void handle_second_tick(struct tm *tick_time, TimeUnits units_changed);
void deinit();


// General
BitmapLayer *load_digit_image_into_slot(TimeSlot *tslot, Layer *parent_layer, GRect frame, int immagine) {
  Slot *slot = &tslot->slot;
  slot->state = 1;
  slot->image = gbitmap_create_with_resource(immagine);

  slot->image_layer = bitmap_layer_create(frame);
  bitmap_layer_set_bitmap(slot->image_layer, slot->image);
  layer_add_child(parent_layer, bitmap_layer_get_layer(slot->image_layer));

  return slot->image_layer;
}

void unload_digit_image_from_slot(Slot *slot) {

  layer_remove_from_parent(bitmap_layer_get_layer(slot->image_layer));
  bitmap_layer_destroy(slot->image_layer);

  gbitmap_destroy(slot->image);

  slot->state = EMPTY_SLOT;
}

// Time
void display_time(struct tm *tick_time, TimeUnits units_changed) {
  ore = tick_time->tm_hour;
  bool notte = (ore >= 0 && ore < 5) ? true : false;
  bool ape = (ore >= 19 && ore < 20) ? true : false;
  bool caffe = (ore >= 10 && ore < 12) ? true : false;
  ore = ore % 12;
  if (ore == 0) {
    ore = 12;
  }
  display_time_value(ore,tick_time->tm_min,notte,ape, caffe);
}

void setCazzata(){
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
	double r = random();
	if(r <= 0.25){
		rzero->immagine = RESOURCE_ID_piu_o_meno;
		runo->immagine = RESOURCE_ID_ora_di_ieri;
    rdue->immagine = RESOURCE_ID_a_quest_ora;
	}else if(r <= 0.5){
		rzero->immagine = RESOURCE_ID_dai_che;
		runo->immagine = RESOURCE_ID_ce_la_fai;
    rdue->immagine = RESOURCE_ID_nera;
	}else if(r <= 0.75){
    rzero->immagine = RESOURCE_ID_ora_di;
		runo->immagine = RESOURCE_ID_rimpiangere;
    rdue->immagine = RESOURCE_ID_ferie;		
	}else{
    rzero->immagine = RESOURCE_ID_ora_di;
		runo->immagine = RESOURCE_ID_tergiversare;
    rdue->immagine = RESOURCE_ID_nera;
	}
  update_time_slot(rzero, 0);
  update_time_slot(runo, 1);
  update_time_slot(rdue, 2);
  return;
}
  


void display_time_value(int ore, int minuti, bool notte, bool ape, bool caffe) {
  TimeSlot *rzero = &righe[0];
  TimeSlot *runo = &righe[1];
  TimeSlot *rdue = &righe[2];
  double r = random();
  if(r < 0.045){
    setCazzata();
    return;
  }
  if(notte){
    double r = random();
    if(r < 0.075){
      rzero->immagine = RESOURCE_ID_notte;
      runo->immagine = RESOURCE_ID_dormi;
      rdue->immagine = RESOURCE_ID_amore;
      update_time_slot(rzero, 0);
      update_time_slot(runo, 1);
      update_time_slot(rdue, 2);
      return;
    }
  }
  if(ape){//aperitivo
    double r = random();
    if(r < 0.075){
      if(r >= 0.0375){
    		rzero->immagine = RESOURCE_ID_ora_di;
        runo->immagine = RESOURCE_ID_farsi;
        rdue->immagine = RESOURCE_ID_birretta;
    	}else{
    		rzero->immagine = RESOURCE_ID_nera;
        runo->immagine = RESOURCE_ID_birretta_pi;
        rdue->immagine = RESOURCE_ID_nera;
    	}
      update_time_slot(rzero, 0);
      update_time_slot(runo, 1);
      update_time_slot(rdue, 2);
      return;
    }
  }
  if(caffe){//caffe
    double r = random();
    if(r < 0.075){
      if(r >= 0.0375){
    		rzero->immagine = RESOURCE_ID_ora_di;
        runo->immagine = RESOURCE_ID_farsi;
        rdue->immagine = RESOURCE_ID_caffeino;
    	}else{
    		rzero->immagine = RESOURCE_ID_nera;
        runo->immagine = RESOURCE_ID_caffeino_pi;
        rdue->immagine = RESOURCE_ID_nera;
    	}
      update_time_slot(rzero, 0);
      update_time_slot(runo, 1);
      update_time_slot(rdue, 2);
      return;
    }
  }
    if(minuti <= 5){
    	double r = random();
    	if(r > 0.375){
    		setCinque(ore);
    	}else{
    		setOtto(ore);
    	}
    }else if(minuti <= 8){
    	double r = random();
    	if(minuti == 8 && r > 0.7){
    		setDieci(ore,true);
    	}else{
    		setOtto(ore);
    	}
    }else if(minuti <= 13){
    	double r = random();
    	if(minuti == 13 && r > 0.9){
    		setUnQuarto(ore,true);
    	}else{
    		quasi = (minuti < 10) ? true : false;
    		setDieci(ore,quasi);
    	}
    }else if(minuti <= 17){
    	double r = random();
    	if(minuti <= 17 && r > 0.9){
    		setVenti(ore,true);
    	}else{
    		quasi = (minuti < 15) ? true : false;
    		setUnQuarto(ore,quasi);
    	}
    }else if(minuti <= 25){
    	double r = random();
    	if(minuti == 25 && r > 0.9){
    		setMezza(ore,quasi);
    	}else{
    		quasi = (minuti < 20) ? true : false;
    		setVenti(ore,quasi);
    	}
    }else if(minuti <= 35){
    	double r = random();
    	if(minuti == 35 && r > 0.9){
    		setQuaranta(ore,quasi);
    	}else if(minuti > 30 && r <= 0.5){
    		setMezzaPassate(ore);
    	}else{
    		quasi = (minuti < 30) ? true : false;
    		setMezza(ore,quasi);
    	}
    }else if(minuti <= 42){
    	double r = random();
    	if(minuti == 42 && r > 0.9){
    		setTreQuarti(ore,quasi);
    	}else{
    		quasi = (minuti < 40) ? true : false;
    		setQuaranta(ore,quasi);
    	}
    }else if(minuti <= 48){
    	double r = random();
    	if(minuti == 48 && r > 0.9){
    		setCinquanta(ore,true);
    	}else{
    		quasi = (minuti < 45) ? true : false;
    		setTreQuarti(ore,quasi);
    	}
    }else if(minuti <= 55){
    	double r = random();
    	if(minuti == 55 && r > 0.9){
    		setCinqueCinque(ore);
    	}else{
    		quasi = (minuti < 50) ? true : false;
    		setCinquanta(ore,quasi);
    	}
    }else{
    	setCinqueCinque(ore);
    }
    TimeSlot *tsuno = &righe[0];
    update_time_slot(tsuno, 0);
    TimeSlot *tsdue = &righe[1];
    update_time_slot(tsdue, 1);
    TimeSlot *tstre = &righe[2];
    update_time_slot(tstre, 2);
    return;
}

void update_time_slot(TimeSlot *time_slot, int num_riga) {
  

    int y = 0;
    if(num_riga == 1){
      y = 57;
    }else if(num_riga == 2){
      y = 113;
    }
    GRect frame = GRect(0, y, 144, 56);
    unload_digit_image_from_slot(&time_slot->slot);
    load_digit_image_into_slot(time_slot, time_layer, frame, time_slot->immagine);
}

void clear_ore(AccelAxisType axis, int32_t direction){
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  TimeUnits mah = false;
  display_time(tick_time, mah );
}


// Handlers
int main(void) {
  init();
  app_event_loop();
  deinit();
}

void init() {
  window = window_create();
  window_stack_push(window, false /* NOT Animated */);
  window_set_background_color(window, GColorBlack);

  Layer *root_layer = window_get_root_layer(window);

  // Time
  for (int i = 0; i < NUMBER_OF_TIME_SLOTS; i++) {
    TimeSlot *time_slot = &righe[i];
    time_slot->slot.number  = i;
    time_slot->immagine  = RESOURCE_ID_nera;
    time_slot->slot.state   = EMPTY_SLOT;
    time_slot->new_state    = EMPTY_SLOT;
    time_slot->updating     = false;
  }

  time_layer = layer_create(GRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
  layer_set_clips(time_layer, true);
  layer_add_child(root_layer, time_layer);


  // Display
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  //display_time(tick_time );
  tick_timer_service_subscribe(MINUTE_UNIT, display_time);
  accel_tap_service_subscribe(clear_ore);
  // Register for Bluetooth connection updates
  connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bluetooth_callback
  });
}

void deinit() {
  // Time
  for (int i = 0; i < NUMBER_OF_TIME_SLOTS; i++) {
    unload_digit_image_from_slot(&righe[i].slot);
  }
  accel_tap_service_unsubscribe();
  tick_timer_service_unsubscribe();
  
  layer_destroy(time_layer);

  window_destroy(window);
}