#include <cstdint>

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

  /**
   * @brief Checks if the position on the map is occupied.
   * @param _u8_affected_track_position The track position to check.
   * @return 1 if occupied, 0 otherwise.
   */
  uint8_t Is_Occupied(uint8_t _u8_affected_track_position);

  /**
   * @brief Returns a token to its home position.
   * @param _u8_affected_track_position The affected track position.
   * @return true if the token is successfully returned home, false otherwise.
   */
  bool Return_Home(uint8_t _u8_affected_track_position);

private:
  uint8_t u8_player_quantity;   /**< Number of human players. */
  uint8_t u8_computer_quantity; /**< Number of computer-controlled players. */
};

/**
 * @class cla_player
 * @brief Description of the cla_player class.
 */
class cla_player : public cla_session {     // Vererbung richtig?
public:
  /**
   * @brief Constructor for the cla_player class.
   * @param _obj_my_session Pointer to the associated session.
   */
  cla_player(cla_session *_obj_my_session);

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
   * @brief Returns the progress of a token on the track.
   * @param _u8_token_number The token number.
   * @return The progress of the token on the track.
   */
  uint8_t Get_Token_Progress(uint8_t _u8_token_number);

  /**
   * @brief Outputs the status of a token.
   * @param _u8_token_number The token number.
   */
  status Get_Status(uint8_t _u8_token_number);

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

protected:
  uint8_t u8_start_position;    ///< The starting position of the player.
  uint8_t u8_token_position[4]; ///< The positions of the player's four tokens.
  cla_session *obj_my_session;  ///< Pointer to the associated session.
};

/**
 * @class cla_computer_player
 * @brief Description of the cla_computer_player class.
 */
class cla_computer_player {
public:
  /**
   * @brief Automatic movement for a computer opponent.
   * @param _u8_dice_value The value of the rolled dice.
   * @return The new position of the token after automatic movement.
   */
  uint8_t Auto_Move(uint8_t _u8_dice_value);

private:
  // mode
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
