#include <cstdint>

namespace LOGIC {

// Forward declaration of cla_player
class cla_player;

// Forward declaration of cla_computer_player
class cla_computer_player;

typedef enum {
  Start = 0,
  Start_Track,
  Start_Finished,
  Start_Track_Finished,
  Error,
  Track,
  Finished,
  Track_Finished,
} status;

/**
 * @class cla_session
 * @brief Description of the cla_session class.
 */
class cla_session {
public:
  /**
   * @brief Constructor for the cla_session class.
   * @param _u8_player_quantity Number of all players.
   * @param _u8_computer_quantity Number of computer-controlled players.
   */
  cla_session(uint8_t _u8_player_quantity, uint8_t _u8_computer_quantity);

  cla_player *array_players[4]; ///< Array of pointers to the players.

  /**
   * @brief Checks if the position on the map is occupied.
   * @param &u8_is_occupied_player_id Reference to variable to store the player
   * ID of the occupied track position.
   * @param &u8_is_occupied_token_number Reference to variable to store the token
   * number of the occupied track position.
   * @param _u8_affected_track_position The track position to check.
   * @return true if occupied, false otherwise.
   */
  bool Is_Occupied(uint8_t &u8_is_occupied_player_id,
                   uint8_t &u8_is_occupied_token_number,
                   uint8_t _u8_affected_track_position);

  /**
   * @brief Returns a token to its home position.
   * @param _u8_affected_track_position The affected track position.
   * @return true if the token is successfully returned home, false otherwise.
   */
  bool Return_Home(uint8_t _u8_affected_track_position);

  uint8_t Get_Player_Quantity(); ///< Returns the number of players.

  uint8_t Get_Computer_Quantity(); ///< Returns the number of computer players.

  uint8_t Get_Is_Occupied_Player_ID(); ///< Returns the ID of the player at the
                                       ///< occupied track position.

  uint8_t Get_Is_Occupied_Token_Number(); ///< Returns the token number on the
                                          ///< occupied track position.
  uint8_t u8_is_occupied_player_id; /**< The ID of the player at the occupied track
                                       position. */
  uint8_t u8_is_occupied_token_number; /**< The token number at the occupied
                                          track position. */

private:
  uint8_t u8_player_quantity;   /**< Number of all players. */
  uint8_t u8_computer_quantity; /**< Number of computer-controlled players. */
};

/**
 * @class cla_player
 * @brief Description of the cla_player class.
 */
class cla_player { 
public:
  /**
   * @brief Constructor for the cla_player class.
   * @param _u8_player_id The ID of the player.
   * @param _u8_start_position The individual starting position of the player.
   * @param _u8_computer_quantity The number of computer controlled players.
   * @param _obj_my_session Pointer to the associated session.
   */
  cla_player(uint8_t _u8_player_id, uint8_t _u8_start_position,
             uint8_t _u8_computer_quantity, cla_session *_obj_my_session);


  /**
   * @brief Calculates the possible position of a token.
   * @param _u8_token_number The token number.
   * @param _u8_dice_value The value of the rolled dice.
   * @return The calculated position of the token.
   */
  uint8_t Calculate_Possible_Position(uint8_t _u8_token_number,
                                      uint8_t _u8_dice_value);

  /**
   * @brief Moves a token on the track.
   * @param _u8_token_number The token number.
   * @param _u8_dice_value The value of the rolled dice.
   * @return The new position of the token.
   */
  uint8_t Move_Token(uint8_t _u8_token_number, uint8_t _u8_dice_value);

  /**
   * @brief Returns the current position of a token.
   * @param _u8_token_number The token number.
   * @return The current position of the token.
   */
  uint8_t Get_Token_Position(uint8_t _u8_token_number);

  /**
   * @brief Changes the position of a token.
   * @param _u8_token_number The token number.
   * @param _u8_new_position The new position of the token.
   * @return The new position of the token.
   */
  uint8_t Set_Token_Position(uint8_t _u8_token_number,
                             uint8_t _u8_new_position);

  /**
   * @brief Returns the progress of a token on the track.
   * @param _u8_token_number The token number.
   * @return The progress of the token on the track.
   */
  uint8_t Get_Token_Progress(uint8_t _u8_token_number);

  /**
   * @brief Outputs the status of player.
   */
  status Get_Player_Status();

  /**
   * @brief Returns the overall progress of the player.
   * @return The overall progress of the player on the track.
   */
  uint8_t Get_Player_Progress();

  /**
   * @brief Checks if the player is a computer opponent.
   * @return true if the player is a computer opponent, false otherwise.
   */
  bool Is_Computer();

  uint8_t
  Get_Start_Position(); ///< Returns the starting position of the player.

  uint8_t Get_Player_ID(); ///< Returns the ID of the player.

  cla_computer_player *array_computer_players[3]; ///< Array of pointers to the
                                                  ///< computer opponents.

protected:
  uint8_t u8_start_position;    ///< The starting position of the player.
  uint8_t u8_token_position[4]; ///< The positions of the player's four tokens.
  uint8_t u8_player_id;         ///< The id of the player.
  cla_session *obj_my_session;  ///< Pointer to the associated session.
};

/**
 * @class cla_computer_player
 * @brief Description of the cla_computer_player class.
 */
class cla_computer_player {
public:
  /**
   * @brief Constructor for the cla_computer_player class.
   * @param _obj_my_player Pointer to the associated session.
   * @param _u8_mode The mode of the computer opponent.
   */
  cla_computer_player(cla_player *_obj_my_player, uint8_t _u8_mode);

  /**
   * @brief Automatic movement for a computer opponent.
   * @param _u8_dice_value The value of the rolled dice.
   * @return The new position of the token after automatic movement.
   */
  uint8_t Auto_Move(uint8_t _u8_dice_value);

  cla_player *obj_my_player; ///< Pointer to the associated player.

protected:
  uint8_t u8_en_mode; ///< The mode of the computer opponent.
};

/**
 * @class cla_manual_player
 * @brief Description of the cla_manual_player class.
 */
class cla_manual_player {
public:
  /**
   * @brief Manual movement for a human player.
   * @param _u8_dice_value The value of the rolled dice.
   * @return The new position of the token after manual movement.
   */
  uint8_t Manual_Move(uint8_t _u8_dice_value);
};

} // namespace LOGIC