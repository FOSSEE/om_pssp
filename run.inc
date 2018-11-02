<?php
function om_pssp_run_form($form, &$form_state)
{
	$options_first = _list_of_om_pssp();
	$url_om_pssp_id = (int) arg(4);
	$om_pssp_data = _om_pssp_information($url_om_pssp_id);
	if ($om_pssp_data == 'Not found') {
		$url_om_pssp_id = '';
	} //$om_pssp_data == 'Not found'
	if (!$url_om_pssp_id) {
		$selected = isset($form_state['values']['om_pssp']) ? $form_state['values']['om_pssp'] : key($options_first);
	} //!$url_om_pssp_id
	elseif ($url_om_pssp_id == '') {
		$selected = 0;
	} //$url_om_pssp_id == ''
	else {
		$selected = $url_om_pssp_id;
	}
	$form = array();
	$form['om_pssp'] = array(
		'#type' => 'select',
		'#title' => t('Title of the om_pssp'),
		'#options' => _list_of_om_pssp(),
		'#default_value' => $selected,
		'#ajax' => array(
			'callback' => 'om_pssp_project_details_callback'
		)
	);
	if (!$url_om_pssp_id) {
		$form['om_pssp_details'] = array(
			'#type' => 'item',
			'#markup' => '<div id="ajax_om_pssp_details"></div>'
		);
		$form['selected_om_pssp'] = array(
			'#type' => 'item',
			'#markup' => '<div id="ajax_selected_om_pssp"></div>'
		);
	} //!$url_om_pssp_id
	else {
		$om_pssp_default_value = $url_om_pssp_id;
		$form['om_pssp_details'] = array(
			'#type' => 'item',
			'#markup' => '<div id="ajax_om_pssp_details">' . _om_pssp_details($om_pssp_default_value) . '</div>'
		);
		$form['selected_om_pssp'] = array(
			'#type' => 'item',
			'#markup' => '<div id="ajax_selected_om_pssp">' . l('Download Power system simulation', 'powersystems/pssp/full-download/project/' . $om_pssp_default_value) . '</div>'
		);
	}
	return $form;
}
function om_pssp_project_details_callback($form, $form_state)
{
	$commands = array();
	$om_pssp_default_value = $form_state['values']['om_pssp'];
	if ($om_pssp_default_value != 0) {
		$form['om_pssp_details']['#markup'] = _om_pssp_details($om_pssp_default_value);
		$om_pssp_details = _om_pssp_information($om_pssp_default_value);
		$provider = user_load($om_pssp_details->uid);
		if ($om_pssp_details->uid > 0) {
			$commands[] = ajax_command_html('#ajax_selected_om_pssp', l('Download Power system simulation', 'powersystems/pssp/full-download/project/' . $om_pssp_default_value));
		} //$om_pssp_details->uid > 0
		else {
			$commands[] = ajax_command_html('#ajax_selected_om_pssp', '');
			$commands[] = ajax_command_html('#ajax_selected_om_pssp', '');
		}
		$commands[] = ajax_command_html('#ajax_om_pssp_details', _om_pssp_details($om_pssp_default_value));
	} //$om_pssp_default_value != 0
	else {
		// $form['lab_experiment_list']['#options'] = _ajax_get_experiment_list();
		//  $commands[] = ajax_command_replace('#ajax_selected_experiment', drupal_render($form['lab_experiment_list']));
		$commands[] = ajax_command_html('#ajax_om_pssp_details', '');
		$commands[] = ajax_command_html('#ajax_selected_om_pssp', '');
		$commands[] = ajax_command_html('#ajax_selected_om_pssp', '');
		$commands[] = ajax_command_data('#ajax_selected_om_pssp', 'form_state_value_select', $form_state['values']['om_pssp']);
	}
	return array(
		'#type' => 'ajax',
		'#commands' => $commands
	);
}
function bootstrap_table_format($headers, $rows)
{
	$thead = "";
	$tbody = "";
	foreach ($headers as $header) {
		$thead .= "<th>{$header}</th>";
	} //$headers as $header
	foreach ($rows as $row) {
		$tbody .= "<tr>";
		foreach ($row as $data) {
			$tbody .= "<td>{$data}</td>";
		} //$row as $data
		$tbody .= "</tr>";
	} //$rows as $row
	$table = "
            <table class='table table-bordered table-hover' style='margin-left:-140px'>
                <thead>{$thead}</thead>
                <tbody>{$tbody}</tbody>
            </table>
        ";
	return $table;
}
/*****************************************************/
function _list_of_om_pssp()
{
	$om_pssp_titles = array(
		'0' => 'Please select...'
	);
	//$lab_titles_q = db_query("SELECT * FROM {om_pssp_proposal} WHERE solution_display = 1 ORDER BY lab_title ASC");
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('approval_status', 3);
	$query->orderBy('project_title', 'ASC');
	$om_pssp_titles_q = $query->execute();
	while ($om_pssp_titles_data = $om_pssp_titles_q->fetchObject()) {
		$om_pssp_titles[$om_pssp_titles_data->id] = $om_pssp_titles_data->project_title . ' (Proposed by ' . $om_pssp_titles_data->name_title . ' ' . $om_pssp_titles_data->contributor_name . ')';
	} //$om_pssp_titles_data = $om_pssp_titles_q->fetchObject()
	return $om_pssp_titles;
}
function _om_pssp_information($proposal_id)
{
	$query = db_select('om_pssp_proposal');
	$query->fields('om_pssp_proposal');
	$query->condition('id', $proposal_id);
	$query->condition('approval_status', 3);
	$om_pssp_q = $query->execute();
	$om_pssp_data = $om_pssp_q->fetchObject();
	if ($om_pssp_data) {
		return $om_pssp_data;
	} //$om_pssp_data
	else {
		return 'Not found';
	}
}
function _om_pssp_details($om_pssp_default_value)
{
	$om_pssp_details = _om_pssp_information($om_pssp_default_value);
	if ($om_pssp_default_value != 0) {
		if($om_pssp_details->reference != NULL){
		$url = '~(?:(https?)://([^\s<]+)|(www\.[^\s<]+?\.[^\s<]+))(?<![\.,:])~i';
	        $reference = preg_replace($url, '<a href="$0" target="_blank" title="$0">$0</a>', $om_pssp_details->reference);
		}else{
		$reference = 'Not provided';
		}
		$form['om_pssp_details']['#markup'] = '<span style="color: rgb(128, 0, 0);"><strong>About the Power system simulation</strong></span></td><td style="width: 35%;"><br />' . '<ul>' . '<li><strong>Proposer Name:</strong> ' . $om_pssp_details->name_title . ' ' . $om_pssp_details->contributor_name . '</li>' . '<li><strong>Title of the Flowhseet:</strong> ' . l($om_pssp_details->project_title,'powersystems/pssp/full-download/project/' . $om_pssp_default_value) . '</li>' . '<li><strong>University:</strong> ' . $om_pssp_details->university . '</li>' . '<li>'.'<strong>Reference:</strong> ' . $reference .'</li>'.'</ul>';
		$details = $form['om_pssp_details']['#markup'];
		return $details;
	} //$om_pssp_default_value != 0
}