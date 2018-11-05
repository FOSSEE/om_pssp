<?php
/**
 * Implementation of hook_mail().
 */
function om_pssp_mail($key, &$message, $params)
{
	global $user;
	$language = $message['language'];
	//$language = user_preferred_language($user);
	switch ($key)
	{
		case 'om_pssp_proposal_received':
			/* initializing data */
			$query = db_select('om_pssp_proposal');
			$query->fields('om_pssp_proposal');
			$query->condition('id', $params['om_pssp_proposal_received']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$phpdate = time( $proposal_data->creation_date );
			$user_data = user_load($params['om_pssp_proposal_received']['user_id']);
			if ($proposal_data->project_guide_name == "NULL" || $proposal_data->project_guide_name == "")
			{
				$project_guide_name = "Not Entered";
			} //$proposal_data->project_guide_name == NULL
			else
			{
				$project_guide_name = $proposal_data->project_guide_name;
			}
			if ($proposal_data->project_guide_email_id == "NULL" || $proposal_data->project_guide_email_id == "")
			{
				$project_guide_email_id = "Not Entered";
			} //$proposal_data->project_guide_email_id == NULL
			else
			{
				$project_guide_email_id = $proposal_data->project_guide_email_id;
			}

			$message['headers'] = $params['om_pssp_proposal_received']['headers'];
			$message['subject'] = t('[!site_name][Power System Simulation Project] Your Power System Simulation Project proposal has been received', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear !user_name,

Thank you for submitting proposal for the Power Systems Simulation Project. The details of your proposal are as below :

Full Name: ' . $proposal_data->name_title . ' ' . $proposal_data->contributor_name . '
Email: ' . $user_data->mail . '
University/Institute: ' . $proposal_data->university . '
City: ' . $proposal_data->city . '
Project Title: ' . $proposal_data->project_title . '
Description of the simulation: ' . $proposal_data->description . '


Your proposal is under review. You will be notified via email about the approval/disapproval within ten working days.


Best Wishes,

!site_name Power Systems Team,
FOSSEE,IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'om_pssp_proposal_disapproved':
			/* initializing data */
			$query = db_select('om_pssp_proposal');
			$query->fields('om_pssp_proposal');
			$query->condition('id', $params['om_pssp_proposal_disapproved']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$phpdate = time( $proposal_data->creation_date );
			$user_data = user_load($params['om_pssp_proposal_disapproved']['user_id']);
			if ($proposal_data->project_guide_name == "NULL" || $proposal_data->project_guide_name == "")
			{
				$project_guide_name = "Not Entered";
			} //$proposal_data->project_guide_name == NULL
			else
			{
				$project_guide_name = $proposal_data->project_guide_name;
			}
			if ($proposal_data->project_guide_email_id == "NULL" || $proposal_data->project_guide_email_id == "")
			{
				$project_guide_email_id = "Not Entered";
			} //$proposal_data->project_guide_email_id == NULL
			else
			{
				$project_guide_email_id = $proposal_data->project_guide_email_id;
			}
			$message['headers'] = $params['om_pssp_proposal_disapproved']['headers'];
			$message['subject'] = t('[!site_name][Power System Simulation Project] Your Power System Simulation Project proposal has been disapproved', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear !user_name,

We regret to inform you that your Power Systems Simulation Project proposal, with following details, has been disapproved.

Full Name: ' . $proposal_data->name_title . ' ' . $proposal_data->contributor_name . '
Email: ' . $user_data->mail . '
University/Institute: ' . $proposal_data->university . '
City: ' . $proposal_data->city . '

Project Title: ' . $proposal_data->project_title . '
Description of the simulation: ' . $proposal_data->description . '

Reason(s) / Feedback: ' . $proposal_data->dissapproval_reason . '

Please note that any files that were uploaded along with the proposal form will be deleted from all our database(s).

Thank you for participating in the Power Systems Simulation Project. You are welcome to submit a new proposal.


Best Wishes,

!site_name Power Systems Team,
FOSSEE,IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'om_pssp_proposal_approved':
			/* initializing data */
			$query = db_select('om_pssp_proposal');
			$query->fields('om_pssp_proposal');
			$query->condition('id', $params['om_pssp_proposal_approved']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['om_pssp_proposal_approved']['user_id']);
			$url = 'https://om.fossee.in/powersystems/pssp/coding-guidelines';
			if ($proposal_data->project_guide_name == "NULL" || $proposal_data->project_guide_name == "")
			{
				$project_guide_name = "Not Entered";
			} //$proposal_data->project_guide_name == NULL
			else
			{
				$project_guide_name = $proposal_data->project_guide_name;
			}
			if ($proposal_data->project_guide_email_id == "NULL" || $proposal_data->project_guide_email_id == "")
			{
				$project_guide_email_id = "Not Entered";
			} //$proposal_data->project_guide_email_id == NULL
			else
			{
				$project_guide_email_id = $proposal_data->project_guide_email_id;
			}
			$message['headers'] = $params['om_pssp_proposal_approved']['headers'];
			$message['subject'] = t('[!site_name][Power Simulation Simulation Project] Your Power Simulation Simulation Project proposal has been approved', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear !user_name,

Congratulations! Your proposal for Power Systems Simulation Project with the following details is approved.

Full Name: ' . $proposal_data->name_title . ' ' . $proposal_data->contributor_name . '
Email: ' . $user_data->mail . '
University/Institute: ' . $proposal_data->university . '
City: ' . $proposal_data->city . '

Project Title: ' . $proposal_data->project_title . '
Description of the simulation: ' . $proposal_data->description . '


Please ensure that ALL the guidelines for coding at https://om.fossee.in/powersystems/pssp/coding-guidelines are strictly followed. Refer https://om.fossee.in/powersystems/pssp/internship for the further procedure for submission of the project. Kindly ensure that the completed model and abstract are submitted within 1 month. 


Best Wishes,

!site_name Power Systems Team,
FOSSEE,IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'om_pssp_proposal_completed':
			/* initializing data */
			$query = db_select('om_pssp_proposal');
			$query->fields('om_pssp_proposal');
			$query->condition('id', $params['om_pssp_proposal_completed']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['om_pssp_proposal_completed']['user_id']);
			if ($proposal_data->project_guide_name == "NULL" || $proposal_data->project_guide_name == "")
			{
				$project_guide_name = "Not Entered";
			} //$proposal_data->project_guide_name == NULL
			else
			{
				$project_guide_name = $proposal_data->project_guide_name;
			}
			if ($proposal_data->project_guide_email_id == "NULL" || $proposal_data->project_guide_email_id == "")
			{
				$project_guide_email_id = "Not Entered";
			} //$proposal_data->project_guide_email_id == NULL
			else
			{
				$project_guide_email_id = $proposal_data->project_guide_email_id;
			}
			$message['headers'] = $params['om_pssp_proposal_completed']['headers'];
			$message['subject'] = t('[!site_name][Power System Simulation Project] Your OpenModelica Power System Simulation Project proposal has been completed', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear !user_name,

Your simulation and abstract for Power Systems Simulation Project at FOSSEE on the following process have been published successfully.


Full Name : ' . $proposal_data->name_title . ' ' . $proposal_data->contributor_name . '
Project Title  : ' . $proposal_data->project_title . '

Kindly access this link to download the same.
https://om.fossee.in/powersystems/pssp/completed-pssp


Thank you for participating in the Power System Simulation Project. You are welcome to propose a new proposal.


Best Wishes,

!site_name Power Systems Team,
FOSSEE,IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'om_pssp_proposal_deleted':
			/* initializing data */
			$query = db_select('om_pssp_proposal');
			$query->fields('om_pssp_proposal');
			$query->condition('id', $params['om_pssp_proposal_deleted']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			$user_data = user_load($params['om_pssp_proposal_deleted']['user_id']);
			
			if ($proposal_data->project_guide_name == "NULL" || $proposal_data->project_guide_name == "")
			{
				$project_guide_name = "Not Entered";
			} //$proposal_data->project_guide_name == NULL
			else
			{
				$project_guide_name = $proposal_data->project_guide_name;
			}
			if ($proposal_data->project_guide_email_id == "NULL" || $proposal_data->project_guide_email_id == "")
			{
				$project_guide_email_id = "Not Entered";
			} //$proposal_data->project_guide_email_id == NULL
			else
			{
				$project_guide_email_id = $proposal_data->project_guide_email_id;
			}
			$message['headers'] = $params['om_pssp_proposal_deleted']['headers'];
			$message['subject'] = t('[!site_name][Power System Simulation Project] Your OpenModelica Power System Simulation Project proposal has been deleted', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['body'] = array(
				'body' => t('
Dear !user_name,

Your  Power Systems Simulation Project proposal with the following details has been deleted:

Full Name : ' . $proposal_data->name_title . ' ' . $proposal_data->contributor_name . '
Email : ' . $user_data->mail . '
University/Institute : ' . $proposal_data->university . '
City : ' . $proposal_data->city . '

Project Title  : ' . $proposal_data->project_title . '
Description of the simulation: ' . $proposal_data->description .'



You can propose a new Power Systems Simulation project.

Best Wishes,

!site_name Power Systems Team,
FOSSEE,IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		/**************************************************************/
		case 'abstract_uploaded':
			// $solution_q = db_query("SELECT * FROM {om_pssp_solution} WHERE id = %d LIMIT 1", $params['abstract_uploaded']['solution_id']);
			$query = db_select('om_pssp_proposal');
			$query->fields('om_pssp_proposal');
			$query->condition('id', $params['abstract_uploaded']['proposal_id']);
			$query->range(0, 1);
			$proposal_data = $query->execute()->fetchObject();
			
			$user_data = user_load($params['abstract_uploaded']['user_id']);
			$message['subject'] = t('[!site_name][Power System Simulation Project] You have uploaded OpenModelica model and abstract', array(
				'!site_name' => variable_get('site_name', '')
			), array(
				'language' => $language->language
			));
			$message['headers'] = $params['abstract_uploaded']['headers'];
			$message['body'] = array(
				'body' => t('
Dear !user_name,

You have successfully uploaded your simulation and abstract for Power Systems Simulation Project with the following details.

Full Name : ' . $proposal_data->name_title . ' ' . $proposal_data->contributor_name . '
Email : ' . $user_data->mail . '
University/Institute : ' . $proposal_data->university . '
City : ' . $proposal_data->city . '

Project Title  : ' . $proposal_data->project_title . '
Description of the simulation: ' . $proposal_data->description .'

You shall be notified via email after the model and abstract are reviewed and approved / disapproved. This may take upto 30 working days.

Best Wishes,

!site_name Power Systems Team,
FOSSEE,IIT Bombay', array(
					'!site_name' => variable_get('site_name', ''),
					'!user_name' => $user_data->name
				), array(
					'language' => $language->language
				))
			);
			break;
		case 'standard':
			$message['subject'] = $params['standard']['subject'];
			$message['body'] = $params['standard']['body'];
			$message['headers'] = $params['standard']['headers'];
			break;
	} //$key
}
