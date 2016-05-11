<?php
/**
* @file
* owasp_xss.inc
*/

function owasp_xss_form() {


    	$form = array();


    	$form['basicdetails']=array(
        '#type'=>'fieldset',
        '#title'=>t('Enter your Basic details below'),
        '#description'=>t('These are all madatory')
      	);

        $form['basicdetails']['name']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your first name'),
            '#default_value'=> '<script>alert(\'hacked\');</script>',
            '#description'=>t('Your first name goes here')
          );
        $form['basicdetails']['last_name']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your Last name'),
            '#default_value'=> '<script>alert(\'hacked\');</script>',
            '#description'=>t('Your Last name goes here')
          );

         $form['basicdetails']['email']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your email'),
            '#default_value'=> 'test@test.fr',
            '#description'=>t('Your email goes here')
          );

  	$form['addressdetails']=array(
        '#type'=>'fieldset',
        '#title'=>t('Enter your Address details below'),
        '#description'=>t('These are all madatory')
      	);

        $form['addressdetails']['country']=array(
            '#type'=>'select',
            '#name'=>'country',
            '#title'=>t('Select your country'),
            '#options'=>array('USA','UK','<script>alert(1);</script>','Japan')
          );
        $form['addressdetails']['city']=array(
            '#type'=>'textfield',
            '#title'=>t('Enter your city'),
            '#default_value'=> '<script>alert(\'hacked\');</script>',
            '#description'=>t('Your city name goes here')
          );
        $form['addressdetails']['localaddress']=array(
            '#type'=>'textarea',
            '#title'=>t('Enter address'),
            '#default_value'=> '<script>alert(\'hacked@hackthem.fr\');</script>',
            '#description'=>t('Your Address name goes here')
          );

     	$form['additionaldetails']=array(
        '#type'=>'fieldset',
        '#title'=>t('Enter your other details below'),
        '#description'=>t('These are all optional')
      	);

        $form['additionaldetails']['gender']=array(
            '#type'=>'radios',
            '#title'=>t('Gender'),
	    	'#default_value' => 0,
            '#options'=>array('Male','Female')
          );

        $form['additionaldetails']['suscribtion']=array(
            '#type'=>'checkboxes',
            '#title'=>t('I want to subscribe for'),
            '#options'=>array('Email newsletter' => t('Email newsletter'),'Offer vouchers'=>t('Offer vouchers'))
          );

        $form['additionaldetails']['birthdate']=array(
            '#type'=>'date',
            '#title'=>t('Birthdate'),
          );

        $form['#attributes']['enctype'] = 'multipart/form-data';

         $form['additionaldetails']['picture']=array(
            '#type'=>'file',
            '#title'=>t('Upload your picture'),
          );

	//security check

	$form['securityCheck']=array(
		'#type'=>'fieldset',
		'#title'=>t('Choose your security valivators'),
		'#description'=>t('These are for security checks (best pratices) :<br>filter_xss() : filters HTML to prevent XSS.<br>check_plain() : encodes special characters in a plain-text string for display as HTML.<br>check_url() : strips dangerous protocols from URI and encodes it for output to HTML.')
	      );

	$form['securityCheck']['validators']=array(
		    '#type'=>'radios',
		    '#title'=>t('I want to use'),
		    '#options'=>array('No filter','filter_xss()','check_plain()','check_url()')
		  );


	    $form['submit']=array(
		'#type'=>'submit',
		'#value'=>t('Submit')
	      );

      return $form;
}


function owasp_xss_form_submit($form, $form_state) {   

	$result="Name= ".$form_state['values']['name']." <br/>";
	$result .="Last Name= ".$form_state['values']['last_name']." <br/>";
	$result .="Email= ".$form_state['values']['email']." <br/>";
	$result .="Country= ".$form['addressdetails']['country']['#options'][$form_state['values']['country']]." <br/>";
	$result .="City= ".$form_state['values']['city']." <br/>";
	$result .="Local Address= ".$form_state['values']['localaddress']." <br/>";




	$result .="Gender= ".$form['additionaldetails']['gender']['#options'][$form_state['values']['gender']]." <br/>";
	
	foreach($form_state['values']['suscribtion'] as $key=>$choice){
	if(!empty($form['additionaldetails']['suscribtion']['#options'][$choice])){
	$result .="Suscribtion= ".$form['additionaldetails']['suscribtion']['#options'][$choice]." <br/>";
	}


	}

	foreach($form_state['values']['validators'] as $key=>$choice){

	if(!empty($form['securityCheck']['validators']['#options'][$choice])){
	$result .="Security Check= ".$form['securityCheck']['validators']['#options'][$choice]." <br/>";
	}
	}


	//$result .="Birth Date= ".$form_state['values']['birthdate'][0]." <br/>";

	//$result .="Suscribtion= ".$form_state['values']['suscribtion']['Email newsletter']." <br/>";
	//$result .="Picture= ".$form_state['values']['picture']." <br/>";

	  drupal_set_message($result);
}




 
function owasp_xss_form_validate($form,&$form_state) {

  if(empty($form_state['values']['name']))
     form_set_error('name','Name cannot be empty');
  else if(empty($form_state['values']['last_name']))
     form_set_error('last_name','Last name cannot be empty');
  else if(filter_var($form_state['values']['email'], FILTER_VALIDATE_EMAIL) == false)
    form_set_error('email','Email is not valid');

 
  foreach($form_state['values']['validators'] as $key=>$choice)
        {
	if(!empty($form['securityCheck']['validators']['#options'][$choice]))
                {
		            
			switch ($form['securityCheck']['validators']['#options'][$choice]) {
				
				case 'filter_xss()' :
					
				  $form_state['values']['name']=filter_xss($form_state['values']['name']);
				  $form_state['values']['last_name']=filter_xss($form_state['values']['last_name']);
				  $form_state['values']['city']=filter_xss($form_state['values']['city']);
				  $form_state['values']['localaddress']=filter_xss($form_state['values']['localaddress']); 
				  break ;
				  
				case 'check_plain()' :
					
				  $form_state['values']['name']=check_plain($form_state['values']['name']);
				  $form_state['values']['last_name']=check_plain($form_state['values']['last_name']);
				  $form_state['values']['city']=check_plain($form_state['values']['city']);
				  $form_state['values']['localaddress']=check_plain($form_state['values']['localaddress']);
				  break ;
				  	
				case 'check_url()' :
					
				  $form_state['values']['name']=check_url($form_state['values']['name']);
				  $form_state['values']['last_name']=check_url($form_state['values']['last_name']);
				  $form_state['values']['city']=check_url($form_state['values']['city']);
				  $form_state['values']['localaddress']=check_url($form_state['values']['localaddress']);
				  break ;
				  			
				  	
				  	
				  	
					}           
				}

         }
}



