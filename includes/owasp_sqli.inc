<?php

/**
* @file
* owasp_sqli.inc
*/

function owasp_sqli_form() {


    	$form = array();

    	$form['credentialsdetails']=array(
        '#type'=>'fieldset',
        '#title'=>t('Enter your login and password'),
        '#description'=>t('These are all madatory')
      	);

        $form['credentialsdetails']['username']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your username'),
            '#default_value'=> 'admin',
            '#description'=>t('Your username goes here')
          );
        $form['credentialsdetails']['password']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your password'),
            '#default_value'=> '\' or \'1\'=\'1',
            '#description'=>t('Your password goes here')
          );

          
	$form['securityCheck']=array(
		'#type'=>'fieldset',
		'#title'=>t('Choose your security valivators'),
		'#description'=>t('These are for security checks (best pratices) :')
	      );

	$form['securityCheck']['validators']=array(
		    '#type'=>'checkboxes',
		    '#title'=>t('I want to activate'),
		    '#options'=>array('PDO'=>t('PDO') )
		  );






	    $form['submit']=array(
		'#type'=>'submit',
		'#value'=>t('Sign in')
	      );

        return $form ;

}


function owasp_sqli_form_submit($form, $form_state) {
   //Depending on the type of form you can add the logic
   //to store the details of the form
   //by adding it in a Drupal table.
   //or sending a mail to the admin
   //Storing in a file
   //or pass it to some other service

     $username = $form_state['values']['username'];
     $password = $form_state['values']['password'];


     db_set_active('owasp');


foreach($form_state['values']['validators'] as $key=>$choice)
        {
	if(!empty($form['securityCheck']['validators']['#options'][$choice]) && $form['securityCheck']['validators']['#options'][$choice] === 'PDO')               

	 { 
          $query = db_query("SELECT * FROM users WHERE username=:username AND password=:password", array(':username'=>$username, ':password'=>$password)); 	 

         }
         else {
           $query = db_query("SELECT * FROM users WHERE username='".$username."' AND password='".$password."'");  
             }
 
	}
 
     db_set_active();
     
	$result = $query->fetchAll();

        if (empty($result)) {
          form_set_error('','Please check you login or password !!!');
         }
        else {
	$details="";
	foreach ($result as $record) {
          
	$details .="Username= ".$record->username." <br/>";
	$details .="Password= ".$record->password." <br/>";
	$details .="First Name= ".$record->first_name." <br/>";	
	$details .="Last Name= ".$record->last_name." <br/>";
	$details .="Card Number= ".$record->card_number." <br/>";
	$details .="Address= ".$record->address." <br/>";
	$details .="City= ".$record->city." <br/>";
	$details .="Province= ".$record->province." <br/>";
	$details .="Post code= ".$record->postcode." <br/>";
	

	}
	drupal_set_message($details);	
        }

     
}



